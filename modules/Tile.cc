module Tile;

import <string>;

import WatanTypes;

using namespace std;

Tile::Tile(ResourceType r, int v)
    : resource(r), value(v) {
}

ResourceType Tile::getResource() const {
    return resource;
}

int Tile::getValue() const {
    return value;
}

string Tile::getResourceStr() const {
    string s = toString(resource);
    size_t len = s.length();

    if (len >= 8) {
        return s;
    }
    size_t totalPad = 8 - len;
    size_t leftPad = totalPad / 2;
    size_t rightPad = totalPad - leftPad;

    return string(leftPad, ' ') + s + string(rightPad, ' ');
}

string Tile::getValueStr() const {
    // In the case of 7 or Netflix, return nothing
    if (value == 7 || resource == ResourceType::Netflix) {
        return "  ";
    }
    return (value < 10 ? " " : "") + to_string(value);
}
