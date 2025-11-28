// Criterion.cc
module Criterion;
import WatanTypes;

Criterion::Criterion()
    : id{ -1 }, owner{ PlayerColour::None }, level{ 0 } {
}

Criterion::Criterion(int id)
    : id{ id }, owner{ PlayerColour::None }, level{ 0 } {
}

int Criterion::getId() const {
    return id;
}

PlayerColour Criterion::getOwner() const {
    return owner;
}

int Criterion::getLevel() const {
    return level;
}

void Criterion::setOwner(PlayerColour p) {
    owner = p;
    level = 1; // Start at Assignment level
}

void Criterion::upgrade() {
    if (level > 0 && level < 3) {
        level++;
    }
}