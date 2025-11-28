export module Game;

import <memory>;
import <iostream>;

import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;

using namespace std;

export class Game {
public:
    Game();

    bool shouldQuit() const { return quit; }
    void requestQuit() { quit = true; }

    void rollDice();
    Player& getPlayer() { return *player; }
    Board& getBoard() { return board; }

private:
    bool quit;
    unique_ptr<Player> player;
    Board board;
    RandomGenerator rng;
    unique_ptr<IDiceStrategy> dice;
};
