export module Game;

import <array>;
import <memory>;
import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import LoadedDiceStrategy;
import WatanTypes;

export class Game {
public:
    Game();

    // Main loop control
    bool isRunning() const;
    void requestQuit();

    // Board access
    Board& getBoard();

    Player& getPlayer();
    const Player& getPlayer() const;

    Player& getPlayer(int index);
    const Player& getPlayer(int index) const;

    int getCurrentPlayerIndex() const;
    PlayerColour getCurrentPlayerColour() const;

    // Turn flow
    void startTurnMessage();
    void nextTurn(); 

    // Dice
    int rollDice();
    void setDiceFair();
    void setDiceLoaded();

private:
    bool quit;
    int currentTurn; 
    int currentPlayer;

    Board board;
    std::array<Player, 4> players;
    RandomGenerator rng;
    std::unique_ptr<IDiceStrategy> dice;
};
