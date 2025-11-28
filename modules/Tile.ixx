export module Tile;

import <string>;
import WatanTypes;

export class Tile {
public:
    Tile(ResourceType r = ResourceType::Netflix, int v = 0);

    ResourceType getResource() const;
    int getValue() const;

    std::string getResourceStr() const;
    std::string getValueStr() const;

private:
    ResourceType resource;
    int value;
};
