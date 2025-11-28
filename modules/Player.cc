// ===== Player.cc =====
module Player;

import <iostream>;
import WatanTypes;
import IDiceStrategy;
import RandomGenerator;

Player::Player(PlayerColour colour)
    : colour{ colour },
    resources{ 0,0,0,0,0 },
    numCourseCriteria{ 0 },
    diceStrat{ nullptr } {
}

PlayerColour Player::getColour() const {
    return colour;
}

void Player::setDiceStrategy(IDiceStrategy* strat) {
    diceStrat = strat;
}

int Player::rollDice(RandomGenerator& rng) {
    if (!diceStrat) return 0;
    return diceStrat->roll(rng);
}

void Player::addResource(ResourceType type, int amount) {
    if (type == ResourceType::Netflix) return;  // not stored
    int idx = static_cast<int>(type);
    if (idx >= 0 && idx < 5) resources[idx] += amount;
}

bool Player::spendResource(ResourceType type, int amount) {
    if (type == ResourceType::Netflix) return false;
    int idx = static_cast<int>(type);
    if (idx < 0 || idx >= 5) return false;
    if (resources[idx] < amount) return false;
    resources[idx] -= amount;
    return true;
}

int Player::getResource(ResourceType type) const {
    if (type == ResourceType::Netflix) return 0;
    int idx = static_cast<int>(type);
    if (idx < 0 || idx >= 5) return 0;
    return resources[idx];
}

void Player::addCriterion(int criterionId) {
    // Level 1 = Assignment
    completedCriteria.push_back({ criterionId, 1 });
    numCourseCriteria++;
}

void Player::improveCriterion(int criterionId) {
    for (auto& p : completedCriteria) {
        if (p.first == criterionId) {
            if (p.second < 3) p.second++;
            return;
        }
    }
}

void Player::addGoal(int goalId) {
    achievedGoals.push_back(goalId);
}

int Player::getCourseCriteria() const {
    return numCourseCriteria;
}

void Player::printCriteria(std::ostream& out) const {
    if (completedCriteria.empty()) {
        out << "  No criteria completed.\n";
        return;
    }
    out << "  Completed Criteria:\n";
    for (const auto& p : completedCriteria) {
        out << "    Criterion " << p.first
            << " (Level " << p.second << ")\n";
    }
}

void Player::printStatus(std::ostream& out) const {
    out << "Player " << toString(colour) << ":\n";
    out << "  Resources:\n";
    out << "    Caffeine: " << resources[0] << "\n";
    out << "    Lab:      " << resources[1] << "\n";
    out << "    Lecture:  " << resources[2] << "\n";
    out << "    Study:    " << resources[3] << "\n";
    out << "    Tutorial: " << resources[4] << "\n";
    out << "  Criteria Count: " << numCourseCriteria << "\n";

    printCriteria(out);
}
