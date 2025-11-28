export module Game;

import <array>;
import <memory>;
import <string>;
import <vector>;

import Player;
import Board;
import RandomGenerator;
import WatanTypes;

using namespace std;

export enum class GamePhase {
    InitialPlacement,
    Normal,
    GameOver
};

export class Game {
public:
    Game();
    ~Game();

    // Game state
    bool isRunning() const;
    void requestQuit();
    GamePhase getGamePhase() const;
    bool getMustRoll() const;
    bool getHasRolled() const;
    bool isWaitingForGeesePlacement() const;
    bool isWaitingForGeeseSteal() const;
    bool isWaitingForInitialGoal() const;

    // Board access
    Board& getBoard();
    const Board& getBoard() const;

    // Player access
    Player& getPlayer();
    const Player& getPlayer() const;
    Player& getPlayer(int index);
    const Player& getPlayer(int index) const;
    int getCurrentPlayerIndex() const;
    PlayerColour getCurrentPlayerColour() const;

    // Game flow
    void startGame();
    void startInitialPlacement();
    void promptInitialPlacement();
    bool handleInitialCriterionPlacement(int criterionId);
    bool handleInitialGoalPlacement(int goalId);
    void startTurnMessage();
    void nextTurn();
    void resetGame();

    // Dice
    int rollDice();
    void setDiceFair();
    void setDiceLoaded();
    void setSeed(unsigned int seed);

    // Actions
    bool completeCriterion(int criterionId);
    bool improveCriterion(int criterionId);
    bool achieveGoal(int goalId);

    // Geese
    void handleGeese();
    bool handleGeesePlacement(int tileIndex);
    bool handleGeeseSteal(const std::string& colourName);
    bool moveGeese(int tileIndex);
    bool stealResource(PlayerColour victim);

    // Resources
    void distributeResources(int roll);

    // Save/Load
    bool saveGame(const std::string& filename) const;
    bool loadGame(const std::string& filename);
    bool loadBoard(const std::string& filename);

private:
    bool quit;
    GamePhase gamePhase;
    int initialPlacementIndex;
    bool waitingForInitialGoal;
    int lastPlacedCriterion;
    bool mustRoll;
    bool hasRolled;
    bool waitingForGeesePlacement;
    bool waitingForGeeseSteal;
    int currentTurn;
    int currentPlayer;
    Board board;
    array<Player, 4> players;
    RandomGenerator rng;
    vector<PlayerColour> geeseVictims;
};
