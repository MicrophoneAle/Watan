module Game;

import <iostream>;
import <sstream>;
import <array>;
import <map>;
import <string>;
import <vector>;

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
    waitingForInitialGoal(false),
    lastPlacedCriterion(-1),
    mustRoll(false),
    hasRolled(false),
    currentTurn(1),
    currentPlayer(0),
    waitingForGeesePlacement(false),
    waitingForGeeseSteal(false),
    board(),
    players{ Player(PlayerColour::Blue),
             Player(PlayerColour::Red),
             Player(PlayerColour::Orange),
             Player(PlayerColour::Yellow) },
    rng(123) {
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

bool Game::isWaitingForGeesePlacement() const {
    return waitingForGeesePlacement;
}

bool Game::isWaitingForGeeseSteal() const {
    return waitingForGeeseSteal;
}

bool Game::isWaitingForInitialGoal() const {
    return waitingForInitialGoal;
}

void Game::startGame() {
    cout << "\n=== Welcome to Students of Watan ===\n\n";
    cout << "Initial placement phase:\n";
    cout << "Each student places 1 criterion and 1 goal.\n";
    cout << "Order: Blue, Red, Orange, Yellow, Yellow, Orange, Red, Blue\n\n";

    startInitialPlacement();
}

void Game::startInitialPlacement() {
    gamePhase = GamePhase::InitialPlacement;
    initialPlacementIndex = 0;
    waitingForInitialGoal = false;
    lastPlacedCriterion = -1;

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
        ? initialPlacementIndex : (7 - initialPlacementIndex);

    currentPlayer = playerIdx;

    if (waitingForInitialGoal) {
        cout << "\nStudent " << toString(players[playerIdx].getColour())
            << ", where do you want to achieve a goal?\n";
    }
    else {
        cout << "\nStudent " << toString(players[playerIdx].getColour())
            << ", where do you want to complete an Assignment?\n";
    }
    cout << "> ";
}

bool Game::handleInitialCriterionPlacement(int criterionId) {
    if (gamePhase != GamePhase::InitialPlacement) {
        cout << "Not in initial placement phase.\n";
        return false;
    }

    if (waitingForInitialGoal) {
        cout << "You must place a goal first.\n";
        return false;
    }

    if (!board.isValidCriterionPlacement(criterionId, getCurrentPlayerColour(), true)) {
        cout << "You cannot build here.\n";
        return false;
    }

    // Update board first
    board.getCriteria()[criterionId].setOwner(getCurrentPlayerColour());

    // Update player after
    getPlayer().addCriterion(criterionId, nullptr);

    cout << "Student " << toString(getCurrentPlayerColour())
        << " completed criterion " << criterionId << ".\n";

    // Now wait for goal placement
    lastPlacedCriterion = criterionId;
    waitingForInitialGoal = true;
    promptInitialPlacement();

    return true;
}

bool Game::handleInitialGoalPlacement(int goalId) {
    if (gamePhase != GamePhase::InitialPlacement) {
        cout << "Not in initial placement phase.\n";
        return false;
    }

    if (!waitingForInitialGoal) {
        cout << "You must place a criterion first.\n";
        return false;
    }

    // Check if goal is adjacent to the criterion just placed
    bool isAdjacent = false;
    vector<int> adjacentGoals = board.getAdjacentGoals(lastPlacedCriterion);

    for (int adjGoal : adjacentGoals) {
        if (adjGoal == goalId) {
            isAdjacent = true;
            break;
        }
    }

    if (!isAdjacent) {
        cout << "Goal must be adjacent to the criterion you just placed (criterion "
            << lastPlacedCriterion << ").\n";
        return false;
    }

    if (board.getGoals()[goalId].getOwner() != PlayerColour::None) {
        cout << "That goal is already achieved.\n";
        return false;
    }

    // Update board
    board.getGoals()[goalId].setOwner(getCurrentPlayerColour());

    // Update player
    getPlayer().addGoal(goalId);

    cout << "Student " << toString(getCurrentPlayerColour())
        << " achieved goal " << goalId << ".\n";

    // Move to next placement
    waitingForInitialGoal = false;
    lastPlacedCriterion = -1;
    initialPlacementIndex++;

    promptInitialPlacement();

    return true;
}

void Game::startTurnMessage() {
    if (gamePhase == GamePhase::InitialPlacement) {
        return;
    }

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
    currentTurn++;
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

    // Apply resource gains to players and print
    for (const auto& [color, resources] : gains) {
        int playerIdx = static_cast<int>(color) - 1;

        if (playerIdx < 0 || playerIdx >= 4) {
            continue;
        }

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

    // Players with 10+ resources lose half randomly
    for (int i = 0; i < 4; i++) {
        int totalResources = players[i].getTotalResources();

        if (totalResources >= 10) {
            int toLose = totalResources / 2;
            cout << "Student " << toString(players[i].getColour())
                << " loses " << toLose << " resources to the geese.\n";
            players[i].loseRandomResources(toLose, rng);
        }
    }

    // Wait for currenet player to place geese
    waitingForGeesePlacement = true;

    cout << "\nStudent " << toString(getCurrentPlayerColour())
        << ", choose where to place the GEESE (tile 0-18, not "
        << board.getGeeseTileIndex() << "):\n";
    cout << "> ";
}

bool Game::handleGeesePlacement(int tileIndex) {
    if (!waitingForGeesePlacement) {
        cout << "Not waiting for geese placement.\n";
        return false;
    }
    if (tileIndex < 0 || tileIndex >= 19) {
        cout << "Invalid tile index. Enter a number from 0 to 18.\n";
        cout << "> ";
        return false;
    }
    if (tileIndex == board.getGeeseTileIndex()) {
        cout << "Geese are already on that tile. Choose a different tile.\n";
        cout << "> ";
        return false;
    }
    board.placeGeese(tileIndex);
    cout << "Geese moved to tile " << tileIndex << ".\n";

    // Find potential victims >:)
    geeseVictims.clear();
    vector<int> criteriaOnTile = board.getCriteriaOnTile(tileIndex);

    for (int critId : criteriaOnTile) {
        const Criterion& crit = board.getCriteria()[critId];

        if (crit.getLevel() > 0 && crit.getOwner() != getCurrentPlayerColour()) {
            int victimIdx = static_cast<int>(crit.getOwner()) - 1;

            if (victimIdx >= 0 && victimIdx < 4 && players[victimIdx].getTotalResources() > 0) {
                // Find new victims
                bool found = false;

                for (PlayerColour v : geeseVictims) {
                    if (v == crit.getOwner()) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    geeseVictims.push_back(crit.getOwner());
                }
            }
        }
    }

    waitingForGeesePlacement = false;

    if (geeseVictims.empty()) {
        cout << "Student " << toString(getCurrentPlayerColour())
            << " has no students to steal from.\n";
        return true;
    }

    // Wait for current player to choose victim
    waitingForGeeseSteal = true;

    cout << "Student " << toString(getCurrentPlayerColour())
        << " can choose to steal from: ";

    // Print out possible victims
    for (size_t i = 0; i < geeseVictims.size(); i++) {
        if (i > 0) cout << ", ";
        cout << toString(geeseVictims[i]);
    }
    cout << "\nChoose a student to steal from:\n> ";

    return true;
}

bool Game::handleGeeseSteal(const string& colourName) {
    if (!waitingForGeeseSteal) {
        cout << "Not waiting for geese steal.\n";
        return false;
    }

    // Parse colour
    PlayerColour victim = PlayerColour::None;
    string lower = colourName;
    for (char& c : lower) {
        c = tolower(c);
    }

    if (lower == "blue") {
        victim = PlayerColour::Blue;
    }
    else if (lower == "red") {
        victim = PlayerColour::Red;
    }
    else if (lower == "orange") {
        victim = PlayerColour::Orange;
    }
    else if (lower == "yellow") {
        victim = PlayerColour::Yellow;
    }

    if (victim == PlayerColour::None) {
        cout << "Invalid colour. Choose from: ";

        for (size_t i = 0; i < geeseVictims.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << toString(geeseVictims[i]);
        }
        cout << "\n> ";
        return false;
    }

    // Check if victim is in the list
    bool validVictim = false;
    for (PlayerColour v : geeseVictims) {
        if (v == victim) {
            validVictim = true;
            break;
        }
    }

    if (!validVictim) {
        cout << "You can only steal from: ";

        for (size_t i = 0; i < geeseVictims.size(); i++) {
            if (i > 0) cout << ", ";
            cout << toString(geeseVictims[i]);
        }
        cout << "\n> ";
        return false;
    }

    // Steal the resource
    int victimIdx = static_cast<int>(victim) - 1;
    ResourceType stolen = players[victimIdx].stealRandomResource(rng);

    if (stolen == ResourceType::Netflix) {
        cout << "Student " << toString(victim) << " has no resources to steal.\n";
    }
    else {
        getPlayer().addResource(stolen, 1);
        cout << "Student " << toString(getCurrentPlayerColour())
            << " steals " << toString(stolen)
            << " from student " << toString(victim) << ".\n";
    }

    waitingForGeeseSteal = false;
    geeseVictims.clear();

    return true;
}

// Wrapper for handleGeesePlacement
bool Game::moveGeese(int tileIndex) {
    return handleGeesePlacement(tileIndex);
}

bool Game::stealResource(PlayerColour victim) {
    int victimIdx = static_cast<int>(victim) - 1;

    // Validate victim
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

// SetDice functions
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

// Build functions
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

    // Check resources
    if (!getPlayer().spendResource(ResourceType::Caffeine, 1) ||
        !getPlayer().spendResource(ResourceType::Lab, 1) ||
        !getPlayer().spendResource(ResourceType::Lecture, 1) ||
        !getPlayer().spendResource(ResourceType::Tutorial, 1)) {

        // Refund resources spent
        getPlayer().addResource(ResourceType::Caffeine, 1);
        getPlayer().addResource(ResourceType::Lab, 1);
        getPlayer().addResource(ResourceType::Lecture, 1);

        cout << "You do not have enough resources.\n";
        return false;
    }

    // Update board first
    board.getCriteria()[criterionId].setOwner(getCurrentPlayerColour());

    // Update player after
    getPlayer().addCriterion(criterionId, nullptr);

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
        // Upgrade to Midterm
        if (!getPlayer().spendResource(ResourceType::Lecture, 2) ||
            !getPlayer().spendResource(ResourceType::Study, 3)) {

            // Refund
            getPlayer().addResource(ResourceType::Lecture, 2);
            getPlayer().addResource(ResourceType::Study, 3);
            cout << "You do not have enough resources.\n";
            return false;
        }

        // Update board
        crit.upgrade();

        // Update player after
        getPlayer().improveCriterion(criterionId);

        cout << "Student " << toString(getCurrentPlayerColour())
            << " improved criterion " << criterionId << " to Midterm.\n";
    }
    else if (currentLevel == 2) {
        // Upgrade to Exam
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

        // Update board
        crit.upgrade();

        // Update player after
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

    // Check resources
    if (!getPlayer().spendResource(ResourceType::Study, 1) ||
        !getPlayer().spendResource(ResourceType::Tutorial, 1)) {

        getPlayer().addResource(ResourceType::Study, 1);
        cout << "You do not have enough resources.\n";
        return false;
    }

    // Update board first
    board.getGoals()[goalId].setOwner(getCurrentPlayerColour());

    // Then update player
    getPlayer().addGoal(goalId);

    cout << "Student " << toString(getCurrentPlayerColour())
        << " achieved goal " << goalId << ".\n";

    return true;
}

void Game::resetGame() {
    // Reset values
    quit = false;
    gamePhase = GamePhase::InitialPlacement;
    initialPlacementIndex = 0;
    waitingForInitialGoal = false;
    lastPlacedCriterion = -1;
    mustRoll = false;
    hasRolled = false;
    waitingForGeesePlacement = false;
    waitingForGeeseSteal = false;
    currentTurn = 1;
    currentPlayer = 0;
    geeseVictims.clear();

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
    // Function stub
    cout << "Save functionality requires fstream (not available).\n";
    cout << "Game state for " << filename << " would be saved here.\n";
    return false;
}

bool Game::loadGame(const string& filename) {
    // Function stub
    cout << "Load functionality requires fstream (not available).\n";
    cout << "Game state from " << filename << " would be loaded here.\n";

    return false;
}
