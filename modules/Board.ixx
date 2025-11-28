export module Board;

import <iostream>;
using namespace std;

export class Board {
public:
    Board() = default;

    void print() const {
        cout << "[Board] Basic board initialized.\n";
    }
};
