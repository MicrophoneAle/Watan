module Tile;

import <iostream>;
import WatanTypes;

using namespace std;

Tile::Tile(ResourceType r, int v) : resource(r), value(v) {}

ResourceType Tile::getResource() const {
    return resource;
}

int Tile::getValue() const {
    return value;
}

void Tile::print() const {
    cout << "[Tile] Resource=" << static_cast<int>(resource)
        << " Value=" << value << "\n";
}
