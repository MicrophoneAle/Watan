module Goal;

import <array>;
import WatanTypes;

Goal::Goal(int id, int c1, int c2)
    : id{ id },
    owner{ PlayerColour::Blue },
    owned{ false },
    adjacentCriteria{ { c1, c2 } } {
}

int Goal::getId() const {
    return id;
}

PlayerColour Goal::getOwner() const {
    return owner;
}

const std::array<int, 2>& Goal::getAdjacentCriteria() const {
    return adjacentCriteria;
}

bool Goal::isOwned() const {
    return owned;
}

void Goal::achieve(PlayerColour colour) {
    if (!owned) {
        owned = true;
        owner = colour;
    }
}

void Goal::setAdjacentCriteria(int c1, int c2) {
    adjacentCriteria[0] = c1;
    adjacentCriteria[1] = c2;
}