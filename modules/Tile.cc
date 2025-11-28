module Tile;

import <iostream>;
import WatanTypes;

Tile::Tile(ResourceType r, int v) : resource(r), value(v) {}
ResourceType Tile::getResource() const { return resource; }
int Tile::getValue() const { return value; }
