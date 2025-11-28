module Tile;
import <string>;
import WatanTypes;

Tile::Tile(ResourceType r, int v)
    : resource(r), value(v) {
}

ResourceType Tile::getResource() const {
    return resource;
}

int Tile::getValue() const {
    return value;
}

std::string Tile::getResourceStr() const {
    std::string s = toString(resource);

    size_t len = s.length();
    if (len >= 8) return s;

    size_t totalPad = 8 - len;
    size_t leftPad = totalPad / 2;
    size_t rightPad = totalPad - leftPad;

    return std::string(leftPad, ' ') + s + std::string(rightPad, ' ');
}

std::string Tile::getValueStr() const {
    if (value == 7 || resource == ResourceType::Netflix) {
        return "  ";
    }

    return (value < 10 ? " " : "") + std::to_string(value);
}