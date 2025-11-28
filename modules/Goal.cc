module Goal;

import WatanTypes;

Goal::Goal() : id{ -1 }, owner{ PlayerColour::Blue } {}

Goal::Goal(int id) : id{ id }, owner{ PlayerColour::Blue } {}

int Goal::getId() const { return id; }

PlayerColour Goal::getOwner() const { return owner; }
void Goal::setOwner(PlayerColour p) { owner = p; }
