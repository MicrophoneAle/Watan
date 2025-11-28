export module Tile;

import <string>;

import WatanTypes;

using namespace std;

export class Tile {
public:
    Tile(ResourceType r = ResourceType::Netflix, int v = 0);

    ResourceType getResource() const;
    int getValue() const;
    string getResourceStr() const;
    string getValueStr() const;

private:
    ResourceType resource;
    int value;
};
