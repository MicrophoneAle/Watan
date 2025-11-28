module Player;

import <iostream>;
import WatanTypes;

using namespace std;

Player::Player(PlayerColour c) : colour(c) {
    resources.fill(0);
}

PlayerColour Player::getColour() const {
    return colour;
}

void Player::printStatus() const {
    cout << "\n[Player Status]\n";
    cout << "Colour: " << static_cast<int>(colour) << "\n";
    cout << "Caffeine: " << resources[0] << "\n";
    cout << "Lab: " << resources[1] << "\n";
    cout << "Lecture: " << resources[2] << "\n";
    cout << "Study: " << resources[3] << "\n";
    cout << "Tutorial: " << resources[4] << "\n";
}

void Player::addResource(ResourceType type, int amount) {
    resources[static_cast<int>(type)] += amount;
}

bool Player::spendResource(ResourceType type, int amount) {
    int idx = static_cast<int>(type);
    if (resources[idx] < amount) return false;
    resources[idx] -= amount;
    return true;
}

int Player::getResource(ResourceType type) const {
    return resources[static_cast<int>(type)];
}
