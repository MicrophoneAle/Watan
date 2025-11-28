export module Game;

import <iostream>;
import <memory>;
import <array>;

import Board;
import Player;
import WatanTypes;
import RandomGenerator;

using namespace std;

export class Game {
public:
    Game(int argc, char* argv[]) : rng(123) {
        players[0] = make_unique<Player>(PlayerColour::Blue);
        players[1] = make_unique<Player>(PlayerColour::Red);
        players[2] = make_unique<Player>(PlayerColour::Orange);
        players[3] = make_unique<Player>(PlayerColour::Yellow);
    }

    void run() {
        cout << "Watan engine initialized.\n";
        board.print();
    }

private:
    Board board;
    array<unique_ptr<Player>, 4> players;
    RandomGenerator rng;
};
