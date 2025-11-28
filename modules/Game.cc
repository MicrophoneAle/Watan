module Game;

import <iostream>;
import <fstream>;
import <sstream>;
import <array>;
import <algorithm>;
import <map>;
import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import LoadedDiceStrategy;
import WatanTypes;

using namespace std;

Game::Game()
    : quit(false),
    gamePhase(GamePhase::InitialPlacement),
    initialPlacementIndex(0),
    mustRoll(false),
    hasRolled(false),
    currentTurn(1),
    currentPlayer(0),
    board(),
    players{ Player(PlayerColour::Blue),
             Player(PlayerColour::Red),
             Player(PlayerColour::Orange),
             Player(PlayerColour::Yellow) },
    rng(123)
{
    // Set all players to fair dice initially
    for (auto& player : players) {
        player.setDiceStrategy(new FairDiceStrategy());
    }
}

Game::~Game() {
    // Clean up dice strategies if needed
}

bool Game::isRunning() const {
    return !quit;
}

void Game::requestQuit() {
    quit = true;
}

Board& Game::getBoard() {
    return board;
}

const Board& Game::getBoard() const {
    return board;
}

Player& Game::getPlayer() {
    return players[currentPlayer];
}

const Player& Game::getPlayer() const {
    return players[currentPlayer];
}

Player& Game::getPlayer(int index) {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid player index");
    return players.at(index);
}

const Player& Game::getPlayer(int index) const {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid player index");
    return players.at(index);
}

int Game::getCurrentPlayerIndex() const {
    return currentPlayer;
}

PlayerColour Game::getCurrentPlayerColour() const {
    return players[currentPlayer].getColour();
}

GamePhase Game::getGamePhase() const {
    return gamePhase;
}

bool Game::getMustRoll() const {
    return mustRoll;
}

bool Game::getHasRolled() const {
    return hasRolled;
}

void Game::startGame() {
    cout << "\n=== Welcome to Students of Watan ===\n\n";
    cout << "Initial placement phase:\n";
    cout << "Order: Blue, Red, Orange, Yellow, Yellow, Orange, Red, Blue\n\n";

    startInitialPlacement();
}

void Game::startInitialPlacement() {
    gamePhase = GamePhase::InitialPlacement;
    initialPlacementIndex = 0;

    promptInitialPlacement();
}

void Game::promptInitialPlacement() {
    if (initialPlacementIndex >= 8) {
        // Initial placement done
        gamePhase = GamePhase::Normal;
        currentPlayer = 0; // Blue starts
        mustRoll = true;
        hasRolled = false;
        startTurnMessage();
        return;
    }

    // Snake order: 0,1,2,3, 3,2,1,0
    int playerIdx = (initialPlacementIndex < 4)
        ? initialPlacementIndex
        : (7 - initialPlacementIndex);

    currentPlayer = playerIdx;

    cout << "\nStudent " << toString(players[playerIdx].getColour())
        << ", where do you want to complete an Assignment?\n";
    cout << "> ";
}

bool Game::handleInitialCriterionPlacement(int criterionId) {
    if (gamePhase != GamePhase::InitialPlacement) {
        cout << "Not in initial placement phase.\n";
        return false;
    }

    if (!board.isValidCriterionPlacement(criterionId, getCurrentPlayerColour(), true)) {
        cout << "You cannot build here.\n";
        return false;
    }

    // Place the criterion
    board.getCriteria()[criterionId].setOwner(getCurrentPlayerColour());
    getPlayer().addCriterion(criterionId, &board);

    cout << "Student " << toString(getCurrentPlayerColour())
        << " completed criterion " << criterionId << ".\n";

    initialPlacementIndex++;
    promptInitialPlacement();

    return true;
}

void Game::startTurnMessage() {
    if (gamePhase == GamePhase::InitialPlacement) return;

    cout << "\n========================================\n";
    cout << "Turn " << currentTurn << "\n";
    cout << "Student " << toString(getCurrentPlayerColour()) << "'s turn.\n";
    cout << "========================================\n";
    getPlayer().printStatus(cout);

    if (mustRoll) {
        cout << "\n** You must roll the dice before taking any actions. **\n";
        cout << "Commands: roll, load, fair\n";
    }
}

void Game::nextTurn() {
    if (gamePhase == GamePhase::InitialPlacement) {
        cout << "Cannot end turn during initial placement.\n";
        return;
    }

    if (mustRoll || !hasRolled) {
        cout << "You must roll the dice before ending your turn.\n";
        return;
    }

    // Check for win condition
    if (getPlayer().getCourseCriteria() >= 10) {
        cout << "\n*** GAME OVER ***\n";
        cout << "Student " << toString(getCurrentPlayerColour()) << " wins!\n";
        cout << "Would you like to play again? (yes/no)\n";
        cout << "> ";

        string response;
        if (cin >> response) {
            if (response == "yes") {
                resetGame();
                return;
            }
        }
        quit = true;
        return;
    }

    // Move to next player
    currentPlayer = (currentPlayer + 1) % 4;
    ++currentTurn;
    mustRoll = true;
    hasRolled = false;

    startTurnMessage();
}

int Game::rollDice() {
    if (gamePhase == GamePhase::InitialPlacement) {
        cout << "Cannot roll dice during initial placement.\n";
        return 0;
    }

    if (hasRolled) {
        cout << "You have already rolled this turn.\n";
        return 0;
    }

    int val = getPlayer().rollDice(rng);
    cout << "Student " << toString(getCurrentPlayerColour())
        << " rolled " << val << ".\n\n";

    hasRolled = true;
    mustRoll = false;

    if (val == 7) {
        handleGeese();
    }
    else {
        distributeResources(val);
    }

    return val;
}

void Game::distributeResources(int roll) {
    vector<pair<PlayerColour, vector<pair<ResourceType, int>>>> gains;
    board.distributeResources(roll, gains);

    if (gains.empty()) {
        cout << "No students gained resources.\n";
        return;
    }

    // Apply gains to players and print
    for (const auto& [color, resources] : gains) {
        int playerIdx = static_cast<int>(color) - 1; // Assuming enum starts at 1
        if (playerIdx < 0 || playerIdx >= 4) continue;

        cout << "Student " << toString(color) << " gained:\n";

        // Aggregate resources by type
        map<ResourceType, int> aggregated;
        for (const auto& [type, amount] : resources) {
            aggregated[type] += amount;
        }

        for (const auto& [type, amount] : aggregated) {
            players[playerIdx].addResource(type, amount);
            cout << "  " << amount << " " << toString(type) << "\n";
        }
    }
    cout << endl;
}

void Game::handleGeese() {
    cout << "\n*** A 7 was rolled! Geese are active! ***\n\n";

    // Step 1: Players with 10+ resources lose half
    for (int i = 0; i < 4; i++) {
        int totalResources = players[i].getTotalResources();
        if (totalResources >= 10) {
            int toLose = totalResources / 2;
            cout << "Student " << toString(players[i].getColour())
                << " loses " << toLose << " resources to the geese.\n";

            players[i].loseRandomResources(toLose, rng);
        }
    }

    // Step 2: Current player moves geese
    cout << "\nStudent " << toString(getCurrentPlayerColour())
        << ", choose where to place the GEESE (tile 0-18, not "
        << board.getGeeseTileIndex() << "):\n";
    cout << "> ";
}

bool Game::moveGeese(int tileIndex) {
    if (tileIndex < 0 || tileIndex >= 19) {
        cout << "Invalid tile index.\n";
        return false;
    }

    if (tileIndex == board.getGeeseTileIndex()) {
        cout << "Geese are already on that tile.\n";
        return false;
    }

    board.placeGeese(tileIndex);
    cout << "Geese moved to tile " << tileIndex << ".\n";

    // Step 3: Steal from a player on that tile
    vector<PlayerColour> victims;
    vector<int> criteriaOnTile = board.getCriteriaOnTile(tileIndex);

    for (int critId : criteriaOnTile) {
        const Criterion& crit = board.getCriteria()[critId];
        if (crit.getLevel() > 0 && crit.getOwner() != getCurrentPlayerColour()) {
            int victimIdx = static_cast<int>(crit.getOwner()) - 1;
            if (victimIdx >= 0 && victimIdx < 4 && players[victimIdx].getTotalResources() > 0) {
                // Add if not already in list
                if (find(victims.begin(), victims.end(), crit.getOwner()) == victims.end()) {
                    victims.push_back(crit.getOwner());
                }
            }
        }
    }

    if (victims.empty()) {
        cout << "Student " << toString(getCurrentPlayerColour())
            << " has no students to steal from.\n";
        return true;
    }

    cout << "Student " << toString(getCurrentPlayerColour())
        << " can choose to steal from: ";
    for (size_t i = 0; i < victims.size(); i++) {
        if (i > 0) cout << ", ";
        cout << toString(victims[i]);
    }
    cout << "\nChoose a student to steal from:\n> ";

    return true;
}

bool Game::stealResource(PlayerColour victim) {
    int victimIdx = static_cast<int>(victim) - 1;
    if (victimIdx < 0 || victimIdx >= 4) {
        cout << "Invalid player.\n";
        return false;
    }

    ResourceType stolen = players[victimIdx].stealRandomResource(rng);
    if (stolen == ResourceType::Netflix) {
        cout << "Student " << toString(victim) << " has no resources to steal.\n";
        return false;
    }

    getPlayer().addResource(stolen, 1);
    cout << "Student " << toString(getCurrentPlayerColour())
        << " steals " << toString(stolen)
        << " from student " << toString(victim) << ".\n";

    return true;
}

void Game::setDiceFair() {
    getPlayer().setDiceStrategy(new FairDiceStrategy());
    cout << "Dice set to FAIR for student "
        << toString(getCurrentPlayerColour()) << ".\n";
}

void Game::setDiceLoaded() {
    getPlayer().setDiceStrategy(new LoadedDiceStrategy());
    cout << "Dice set to LOADED for student "
        << toString(getCurrentPlayerColour()) << ".\n";
}

bool Game::completeCriterion(int criterionId) {
    if (gamePhase == GamePhase::InitialPlacement) {
        return handleInitialCriterionPlacement(criterionId);
    }

    if (mustRoll) {
        cout << "You must roll the dice first.\n";
        return false;
    }

    if (!board.isValidCriterionPlacement(criterionId, getCurrentPlayerColour(), false)) {
        cout << "You cannot build here.\n";
        return false;
    }

    // Check resources: 1 Caffeine, 1 Lab, 1 Lecture, 1 Tutorial
    if (!getPlayer().spendResource(ResourceType::Caffeine, 1) ||
        !getPlayer().spendResource(ResourceType::Lab, 1) ||
        !getPlayer().spendResource(ResourceType::Lecture, 1) ||
        !getPlayer().spendResource(ResourceType::Tutorial, 1)) {

        // Refund any spent
        getPlayer().addResource(ResourceType::Caffeine, 1);
        getPlayer().addResource(ResourceType::Lab, 1);
        getPlayer().addResource(ResourceType::Lecture, 1);

        cout << "You do not have enough resources.\n";
        return false;
    }

    // Actually spend the resources (already done above)
    board.getCriteria()[criterionId].setOwner(getCurrentPlayerColour());
    getPlayer().addCriterion(criterionId, &board);

    cout << "Student " << toString(getCurrentPlayerColour())
        << " completed criterion " << criterionId << " (Assignment).\n";

    return true;
}

bool Game::improveCriterion(int criterionId) {
    if (mustRoll) {
        cout << "You must roll the dice first.\n";
        return false;
    }

    Criterion& crit = board.getCriteria()[criterionId];

    if (crit.getOwner() != getCurrentPlayerColour()) {
        cout << "You do not own this criterion.\n";
        return false;
    }

    int currentLevel = crit.getLevel();
    if (currentLevel >= 3) {
        cout << "This criterion is already at maximum level (Exam).\n";
        return false;
    }

    // Check resources based on next level
    if (currentLevel == 1) {
        // Upgrade to Midterm: 2 Lecture, 3 Study
        if (!getPlayer().spendResource(ResourceType::Lecture, 2) ||
            !getPlayer().spendResource(ResourceType::Study, 3)) {

            getPlayer().addResource(ResourceType::Lecture, 2);
            cout << "You do not have enough resources.\n";
            return false;
        }
        crit.upgrade();
        getPlayer().improveCriterion(criterionId);
        cout << "Student " << toString(getCurrentPlayerColour())
            << " improved criterion " << criterionId << " to Midterm.\n";
    }
    else if (currentLevel == 2) {
        // Upgrade to Exam: 3 Caffeine, 2 Lab, 2 Lecture, 1 Tutorial, 2 Study
        if (!getPlayer().spendResource(ResourceType::Caffeine, 3) ||
            !getPlayer().spendResource(ResourceType::Lab, 2) ||
            !getPlayer().spendResource(ResourceType::Lecture, 2) ||
            !getPlayer().spendResource(ResourceType::Tutorial, 1) ||
            !getPlayer().spendResource(ResourceType::Study, 2)) {

            // Refund
            getPlayer().addResource(ResourceType::Caffeine, 3);
            getPlayer().addResource(ResourceType::Lab, 2);
            getPlayer().addResource(ResourceType::Lecture, 2);
            getPlayer().addResource(ResourceType::Tutorial, 1);

            cout << "You do not have enough resources.\n";
            return false;
        }
        crit.upgrade();
        getPlayer().improveCriterion(criterionId);
        cout << "Student " << toString(getCurrentPlayerColour())
            << " improved criterion " << criterionId << " to Exam.\n";
    }

    return true;
}

bool Game::achieveGoal(int goalId) {
    if (mustRoll) {
        cout << "You must roll the dice first.\n";
        return false;
    }

    if (!board.isValidGoalPlacement(goalId, getCurrentPlayerColour())) {
        cout << "You cannot build here.\n";
        return false;
    }

    // Check resources: 1 Study, 1 Tutorial
    if (!getPlayer().spendResource(ResourceType::Study, 1) ||
        !getPlayer().spendResource(ResourceType::Tutorial, 1)) {

        getPlayer().addResource(ResourceType::Study, 1);
        cout << "You do not have enough resources.\n";
        return false;
    }

    board.getGoals()[goalId].setOwner(getCurrentPlayerColour());
    getPlayer().addGoal(goalId);

    cout << "Student " << toString(getCurrentPlayerColour())
        << " achieved goal " << goalId << ".\n";

    return true;
}

void Game::resetGame() {
    quit = false;
    gamePhase = GamePhase::InitialPlacement;
    initialPlacementIndex = 0;
    mustRoll = false;
    hasRolled = false;
    currentTurn = 1;
    currentPlayer = 0;

    // Reset board and players
    board = Board();
    players = {
        Player(PlayerColour::Blue),
        Player(PlayerColour::Red),
        Player(PlayerColour::Orange),
        Player(PlayerColour::Yellow)
    };

    for (auto& player : players) {
        player.setDiceStrategy(new FairDiceStrategy());
    }

    startGame();
}

bool Game::saveGame(const string& filename) const {
    ofstream out(filename);
    if (!out) {
        cout << "Failed to open file for saving.\n";
        return false;
    }

    // Save current turn (which player should go next)
    out << currentPlayer << "\n";

    // Save each player's data
    for (const auto& player : players) {
        player.save(out);
    }

    // Save board state (resources and values)
    const auto& tiles = board.getTiles();
    for (const auto& tile : tiles) {
        int resType = static_cast<int>(tile.getResource());
        out << resType << " " << tile.getValue() << " ";
    }
    out << "\n";

    // Save geese position
    out << board.getGeeseTileIndex() << "\n";

    cout << "Game saved to " << filename << "\n";
    return true;
}

bool Game::loadGame(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "Failed to open file for loading.\n";
        return false;
    }

    // Load current player
    in >> currentPlayer;

    // Load each player
    for (auto& player : players) {
        player.load(in, &board);
    }

    // Load board state
    for (int i = 0; i < 19; i++) {
        int resType, value;
        in >> resType >> value;
        // Reconstruct tile - this requires Board to have a setter
        // For now, we'll skip this and assume initializeTiles handles it
    }

    // Load geese position
    int geesePos;
    in >> geesePos;
    board.placeGeese(geesePos);

    gamePhase = GamePhase::Normal;
    mustRoll = true;
    hasRolled = false;

    cout << "Game loaded from " << filename << "\n";
    startTurnMessage();

    return true;
}