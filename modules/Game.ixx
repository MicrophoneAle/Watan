export module Game;

import <memory>;
import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import LoadedDiceStrategy;

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
