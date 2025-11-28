export module Board;

import <array>;
import <vector>;
import <iostream>;
import <string>;
import Tile;
import Criterion;
import Goal;
import WatanTypes;

export class Board {
private:
    // Index of the tile containing the geese (-1 => not on board yet)
    int geeseTileIndex;

    // 19 tile objects
    std::vector<Tile> tiles;

    // 54 criteria (vertices)
    std::vector<Criterion> criteria;

    // 72 goals (edges)
    std::vector<Goal> goals;

    // For each tile, the 6 criterion indices around it (in clockwise order).
    // Indices are 0..53, matching the assignment spec diagram.
    std::vector<std::array<int, 6>> tileCoords;

public:
    Board(); // Constructor

    // Version 6/8 additions
    void initializeTiles();                  // Load 19 tiles with resource + value
    void distributeRessources(int roll);     // Distribute based on dice roll (still simple in v8)

    // Geese system
    void placeGeese(int tileIndex);
    int getGeeseTileIndex() const;

    // Placement validation (stubs for now, to be fully implemented in later versions)
    bool isValidCriterionPlacement(int criterionIndex);
    bool isValidGoalPlacement(int goalIndex);

    // Accessors (useful for later versions)
    const std::vector<Tile>& getTiles() const;
    const std::vector<Criterion>& getCriteria() const;
    const std::vector<Goal>& getGoals() const;

    // Display
    void display(std::ostream& out) const;
    void print() const;

    friend std::ostream& operator<<(std::ostream& out, const Board& board);
};