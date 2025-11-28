export module Player;

import <array>;
import <iostream>;
import WatanTypes;

using namespace std;

export class Player {
public:
    Player(PlayerColour c);

    PlayerColour getColour() const;

    void addResource(ResourceType r, int amt);
    int getResource(ResourceType r) const;

    void printStatus() const;

private:
    PlayerColour colour;
    array<int, 5> resources;
};
