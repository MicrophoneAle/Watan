export module Game;

import <memory>;
import <iostream>;
import <string>;

import Player;
import Board;

using namespace std;

export class Game {
public:
    Game();

    bool shouldQuit() const { return quit; }
    void requestQuit() { quit = true; }

    Player& getCurrentPlayer();
    Board& getBoard();

private:
    bool quit;
    unique_ptr<Player> player;
    Board board;
};
