module Tile;

import <iostream>;
import WatanTypes;

Tile::Tile(ResourceType r, int v) : resource(r), value(v) {}
ResourceType Tile::getResource() const { return resource; }
int Tile::getValue() const { return value; }

// Returns the string name (e.g., "LAB")
std::string Tile::getResourceStr() const {
    // 1. Get the raw string (e.g., "LAB")
    std::string s = toString(resource);

    // 2. Calculate needed padding to reach 8 characters
    int len = s.length();
    if (len >= 8) {
        return s; // Already 8+ chars (CAFFEINE, TUTORIAL)
    }

    int totalPad = 8 - len;
    int leftPad = totalPad / 2;       // Integer division (e.g., 5/2 = 2)
    int rightPad = totalPad - leftPad; // Remaining spaces (e.g., 5-2 = 3)

    // 3. Return:  [Spaces] + "LAB" + [Spaces]
    return std::string(leftPad, ' ') + s + std::string(rightPad, ' ');
}

// Returns the value formatted for the board (e.g., " 9" or "  ")
string Tile::getValueStr() const {
    // If it's a 7 or Netflix/Geese tile, show spaces instead of a number
    if (value == 7 || resource == ResourceType::Netflix) {
        return "  ";
    }

    // Add a padding space for single digits so the ASCII art aligns
    return (value < 10 ? " " : "") + std::to_string(value);
}
