module Criterion;

import WatanTypes;

Criterion::Criterion() : id{ -1 }, owner{ PlayerColour::Blue }, level{ 0 } {}

Criterion::Criterion(int id)
    : id{ id }, owner{ PlayerColour::Blue }, level{ 0 } {
}

int Criterion::getId() const { return id; }
PlayerColour Criterion::getOwner() const { return owner; }
int Criterion::getLevel() const { return level; }

void Criterion::setOwner(PlayerColour p) {
    owner = p;
    level = 1;
}

void Criterion::upgrade() {
    if (level < 3 && level > 0) level++;
}
