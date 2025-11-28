export module Board;

import <vector>;
import <array>;
import <iostream>;
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
    const std::vector<Criterion>& getCriteria() const;
    const std::vector<Goal>& getGoals() const;

    int getGeeseTileIndex() const;

    // Validation
    bool isValidCriterionPlacement(int id) const;
    bool isValidGoalPlacement(int id) const;

    // Distribution
    void distributeResources(int roll);

    // Display
    void print() const;
    void display(std::ostream& out) const;

private:
    std::vector<Tile> tiles;
    std::vector<Criterion> criteria;
    std::vector<Goal> goals;

    std::vector<std::array<int, 6>> tileCoords;

    int geeseTileIndex;

    // internal helpers
    bool adjacentCriterionExists(int id) const;
    bool adjacentGoalExists(int id) const;
};

export std::ostream& operator<<(std::ostream& out, const Board& b);
