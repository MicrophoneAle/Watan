export module Player;

import <iostream>;
import <array>;
import WatanTypes;

using namespace std;

export class Player {
public:
    Player(PlayerColour c);

    PlayerColour getColour() const;
    void printStatus() const;

    void addResource(ResourceType type, int amount);
    bool spendResource(ResourceType type, int amount);
    int getResource(ResourceType type) const;

private:
    PlayerColour colour;
    array<int, 5> resources; // Caffeine, Lab, Lecture, Study, Tutorial
};
