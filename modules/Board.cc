module Board;

import <vector>;
import <iostream>;
import Tile;
import WatanTypes;

using namespace std;

Board::Board() {
    // Simple 3-tile demo board
    tiles.emplace_back(ResourceType::Caffeine, 4);
    tiles.emplace_back(ResourceType::Study, 6);
    tiles.emplace_back(ResourceType::Lecture, 9);
}

void Board::print() const {
    cout << "[Board] " << tiles.size() << " tiles loaded.\n";
    for (const auto& t : tiles) {
        t.print();
    }
}
