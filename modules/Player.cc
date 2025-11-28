module Player;

import <array>;
import <iostream>;
import WatanTypes;

using namespace std;

Player::Player(PlayerColour c) : colour(c) {
    resources.fill(0);
}

PlayerColour Player::getColour() const {
    return colour;
}

void Player::addResource(ResourceType r, int amt) {
    resources[static_cast<int>(r)] += amt;
}

int Player::getResource(ResourceType r) const {
    return resources[static_cast<int>(r)];
}

void Player::printStatus() const {
    cout << "[Player] Colour=" << static_cast<int>(colour) << "\n";
    cout << "Resources: ";
    for (int x : resources) {
        cout << x << ' ';
    }
    cout << "\n";
}
