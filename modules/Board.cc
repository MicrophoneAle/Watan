export module Board;

import <iostream>;

using namespace std;

export class Board {
public:
    Board() {}

    void print() const {
        cout << "[Board] Boot OK (stub).\n";
    }
};
