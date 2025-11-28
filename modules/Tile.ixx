export module Tile;

import <iostream>;
import WatanTypes;

using namespace std;

export class Tile {
public:
    Tile(ResourceType r, int v);

    ResourceType getResource() const;
    int getValue() const;
    void print() const;

private:
    ResourceType resource;
    int value;
};
