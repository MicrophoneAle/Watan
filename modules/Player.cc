export module Player;

import WatanTypes;

using namespace std;

export class Player {
public:
    Player(PlayerColour c) : colour(c) {}

    PlayerColour getColour() const {
        return colour;
    }

private:
    PlayerColour colour;
};
