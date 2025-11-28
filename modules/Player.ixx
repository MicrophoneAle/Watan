// ===== Player.ixx =====
export module Player;

import <array>;
import <vector>;
import <iostream>;
import WatanTypes;
import IDiceStrategy;
import RandomGenerator;

// Version 9: Player stores basic resource counts,
// completed criteria, achieved goals, and uses dice strategies.

export class Player {
public:
    Player(PlayerColour colour);

    // Colour
    PlayerColour getColour() const;

    // Dice strategy
    void setDiceStrategy(IDiceStrategy* strat);
    int rollDice(RandomGenerator& rng);

    // Resources
    void addResource(ResourceType type, int amount);
    bool spendResource(ResourceType type, int amount);
    int getResource(ResourceType type) const;

    // Criteria + goals
    void addCriterion(int criterionId);
    void improveCriterion(int criterionId);
    void addGoal(int goalId);

    int getCourseCriteria() const;

    // Output
    void printStatus(std::ostream& out) const;
    void printCriteria(std::ostream& out) const;

private:
    PlayerColour colour;

    // Caffeine, Lab, Lecture, Study, Tutorial
    std::array<int, 5> resources;

    // (criterionId, level [1–3])
    std::vector<std::pair<int, int>> completedCriteria;

    // goal ids
    std::vector<int> achievedGoals;

    int numCourseCriteria;

    // Strategy pointer (non-owning)
    IDiceStrategy* diceStrat;

    // Placeholder for event cards (unused in Option C)
    std::vector<int> eventCards;
};
