export module Player;
import <array>;
import <vector>;
import <iostream>;
import WatanTypes;
import IDiceStrategy;
import RandomGenerator;

// Forward declaration
class Board;

export class Player {
public:
    Player(PlayerColour colour);
    ~Player();

    // Colour
    PlayerColour getColour() const;

    // Dice strategy
    void setDiceStrategy(IDiceStrategy* strat);
    int rollDice(RandomGenerator& rng);

    // Resources
    void addResource(ResourceType type, int amount);
    bool spendResource(ResourceType type, int amount);
    int getResource(ResourceType type) const;
    int getTotalResources() const;
    void loseRandomResources(int count, RandomGenerator& rng);
    ResourceType stealRandomResource(RandomGenerator& rng);

    // Criteria + goals
    void addCriterion(int criterionId, Board* board);
    void improveCriterion(int criterionId);
    void addGoal(int goalId);
    int getCourseCriteria() const;
    void recalculateCourseCriteria();

    // Study buddies and bonuses
    void addStudyBuddy();
    int getStudyBuddies() const;
    void setLargestStudyGroup(bool has);
    void setLongestGoals(bool has);
    bool getLargestStudyGroup() const;
    bool getLongestGoals() const;

    // Output
    void printStatus(std::ostream& out) const;
    void printCriteria(std::ostream& out) const;

    // Save/Load
    void save(std::ostream& out) const;
    void load(std::istream& in, Board* board);

private:
    PlayerColour colour;
    std::array<int, 5> resources; // Caffeine, Lab, Lecture, Study, Tutorial
    std::vector<std::pair<int, int>> completedCriteria; // (criterionId, level)
    std::vector<int> achievedGoals;
    int numCourseCriteria;
    int numStudyBuddies;
    bool hasLargestStudyGroup;
    bool hasLongestGoals;
    IDiceStrategy* diceStrat; // Non-owning in the sense we delete it ourselves
};