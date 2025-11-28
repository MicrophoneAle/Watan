module Player;

import <iostream>;
import <vector>;
import <string>;
import WatanTypes;
import IDiceStrategy;
import RandomGenerator;

// Forward declaration only - DO NOT import Board
class Board;

using namespace std;

Player::Player(PlayerColour colour)
    : colour{ colour },
    resources{ 0,0,0,0,0 },
    numCourseCriteria{ 0 },
    numStudyBuddies{ 0 },
    hasLargestStudyGroup{ false },
    hasLongestGoals{ false },
    diceStrat{ nullptr } {
}

Player::~Player() {
    delete diceStrat;
}

PlayerColour Player::getColour() const {
    return colour;
}

void Player::setDiceStrategy(IDiceStrategy* strat) {
    if (diceStrat) delete diceStrat;
    diceStrat = strat;
}

int Player::rollDice(RandomGenerator& rng) {
    if (!diceStrat) return 0;
    return diceStrat->roll(rng);
}

void Player::addResource(ResourceType type, int amount) {
    if (type == ResourceType::Netflix) return;
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

int Player::getTotalResources() const {
    int total = 0;
    for (int r : resources) total += r;
    return total;
}

void Player::loseRandomResources(int count, RandomGenerator& rng) {
    int totalRes = getTotalResources();
    if (totalRes == 0 || count <= 0) return;

    cout << "They lose:\n";

    for (int i = 0; i < count && getTotalResources() > 0; i++) {
        // Pick a random resource type to lose
        vector<ResourceType> available;
        for (int j = 0; j < 5; j++) {
            if (resources[j] > 0) {
                available.push_back(static_cast<ResourceType>(j));
            }
        }

        if (available.empty()) break;

        int idx = rng.intInRange(0, static_cast<int>(available.size()) - 1);
        ResourceType toLose = available[idx];

        spendResource(toLose, 1);
        cout << "  1 " << toString(toLose) << "\n";
    }
}

ResourceType Player::stealRandomResource(RandomGenerator& rng) {
    vector<ResourceType> available;
    for (int i = 0; i < 5; i++) {
        if (resources[i] > 0) {
            available.push_back(static_cast<ResourceType>(i));
        }
    }

    if (available.empty()) return ResourceType::Netflix;

    int idx = rng.intInRange(0, static_cast<int>(available.size()) - 1);
    ResourceType stolen = available[idx];
    spendResource(stolen, 1);

    return stolen;
}

void Player::addCriterion(int criterionId, Board* /*board*/) {
    // Check if already have this criterion
    for (const auto& p : completedCriteria) {
        if (p.first == criterionId) return;
    }

    completedCriteria.push_back({ criterionId, 1 });
    recalculateCourseCriteria();

    // NOTE: Board update is handled by Game.cc when it calls board.getCriteria()[id].setOwner()
}

void Player::improveCriterion(int criterionId) {
    for (auto& p : completedCriteria) {
        if (p.first == criterionId) {
            if (p.second < 3) {
                p.second++;
                recalculateCourseCriteria();
            }
            return;
        }
    }
}

void Player::addGoal(int goalId) {
    achievedGoals.push_back(goalId);
    recalculateCourseCriteria();
}

void Player::recalculateCourseCriteria() {
    numCourseCriteria = 0;

    // Count from criteria (each criterion = 1)
    numCourseCriteria += static_cast<int>(completedCriteria.size());

    // Add bonuses
    if (hasLargestStudyGroup) numCourseCriteria += 2;
    if (hasLongestGoals) numCourseCriteria += 2;
}

int Player::getCourseCriteria() const {
    return numCourseCriteria;
}

void Player::addStudyBuddy() {
    numStudyBuddies++;
}

int Player::getStudyBuddies() const {
    return numStudyBuddies;
}

void Player::setLargestStudyGroup(bool has) {
    hasLargestStudyGroup = has;
    recalculateCourseCriteria();
}

void Player::setLongestGoals(bool has) {
    hasLongestGoals = has;
    recalculateCourseCriteria();
}

bool Player::getLargestStudyGroup() const {
    return hasLargestStudyGroup;
}

bool Player::getLongestGoals() const {
    return hasLongestGoals;
}

void Player::printCriteria(std::ostream& out) const {
    if (completedCriteria.empty()) {
        out << "  No criteria completed.\n";
        return;
    }

    out << toString(colour) << " has completed:\n";
    for (const auto& p : completedCriteria) {
        out << p.first << " " << p.second << "\n";
    }
}

void Player::printStatus(std::ostream& out) const {
    out << toString(colour) << " has " << numCourseCriteria << " course criteria, "
        << resources[0] << " caffeines, "
        << resources[1] << " labs, "
        << resources[2] << " lectures, "
        << resources[3] << " studies, and "
        << resources[4] << " tutorials.\n";
}

void Player::save(std::ostream& out) const {
    // Resources
    for (int i = 0; i < 5; i++) {
        out << resources[i] << " ";
    }

    // Goals
    out << "g ";
    for (int goalId : achievedGoals) {
        out << goalId << " ";
    }

    // Criteria
    out << "c ";
    for (const auto& [id, level] : completedCriteria) {
        out << id << " " << level << " ";
    }

    out << "\n";
}

void Player::load(std::istream& in, Board* /*board*/) {
    // Load resources
    for (int i = 0; i < 5; i++) {
        in >> resources[i];
    }

    // Load goals
    string marker;
    in >> marker; // "g"

    achievedGoals.clear();
    int goalId;
    while (in >> goalId) {
        if (goalId < 0) break;
        achievedGoals.push_back(goalId);

        // NOTE: Board update is handled by Game.cc after calling player.load()

        // Check for "c" marker
        char next = in.peek();
        if (next == 'c') break;
    }

    // Load criteria
    in >> marker; // "c"

    completedCriteria.clear();
    int critId, level;
    while (in >> critId >> level) {
        completedCriteria.push_back({ critId, level });

        // NOTE: Board update is handled by Game.cc after calling player.load()

        // Check if line ends
        if (in.peek() == '\n') break;
    }

    recalculateCourseCriteria();
}