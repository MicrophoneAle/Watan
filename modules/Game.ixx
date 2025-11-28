// ===== Game.ixx =====
export module Game;

import <memory>;
import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import LoadedDiceStrategy;

// Game orchestrates the main loop and owns Board, Player, RNG and dice strategy.
// Version 9: still single-player (Blue) with fair/loaded dice switching.
export class Game {
public:
    Game();

    bool isRunning() const;
    void requestQuit();

    Board& getBoard();
    Player& getPlayer();
    int rollDice();

    void setDiceFair();
    void setDiceLoaded();

private:
    bool quit;
    Board board;
    Player player;
    RandomGenerator rng;
    std::unique_ptr<IDiceStrategy> dice;
};
