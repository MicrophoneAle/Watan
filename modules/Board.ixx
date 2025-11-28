export module Board;

import <vector>;
import <iostream>;
import Tile;
import WatanTypes;

using namespace std;

export class Board {
public:
    Board();

    void print() const;

private:
    vector<Tile> tiles;
};
