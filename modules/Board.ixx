export module Board;

import <vector>;
import <array>;
import <iostream>;
import <map>;

import Tile;
import Criterion;
import Goal;
import WatanTypes;

export class Board {
public:
    Board();

    // Setup
    void initializeTiles();
    void placeGeese(int tileIndex);

    // Core accessors
    const std::vector<Tile>& getTiles() const;
    std::vector<Tile>& getTiles();

    const std::vector<Criterion>& getCriteria() const;
    std::vector<Criterion>& getCriteria();

    const std::vector<Goal>& getGoals() const;
    std::vector<Goal>& getGoals();

    int getGeeseTileIndex() const;

    // Validation
    bool isValidCriterionPlacement(int id, PlayerColour player, bool isInitialPlacement = false) const;
    bool isValidGoalPlacement(int id, PlayerColour player) const;
    bool isConnectedToPlayerGoal(int criterionId, PlayerColour player) const;

    // Adjacency helpers
    std::vector<int> getAdjacentCriteria(int criterionId) const;
    std::vector<int> getAdjacentGoals(int criterionId) const;
    std::vector<int> getCriteriaOnTile(int tileIndex) const;

    // Distribution
    void distributeResources(int roll, std::vector<std::pair<PlayerColour, std::vector<std::pair<ResourceType, int>>>>& gains);

    // Display
    void print() const;
    void display(std::ostream& out) const;
    std::string getCriterionDisplay(int id) const;
    std::string getGoalDisplay(int id) const;

private:
    std::vector<Tile> tiles;
    std::vector<Criterion> criteria;
    std::vector<Goal> goals;
    std::vector<std::array<int, 6>> tileCoords;
    int geeseTileIndex;

    // Adjacent helpers
    bool adjacentCriterionExists(int id) const;
};

export std::ostream& operator<<(std::ostream& out, const Board& b);
