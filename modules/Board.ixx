export module Board;

import <vector>;
import <iostream>;
import <string>;

import Tile;
import Criterion;
import Goal;
import WatanTypes;

export class Board {
public:
    Board();

    // Version 6+
    void initializeTiles();
    void placeGeese(int tileIndex);
    int getGeeseTileIndex() const;

    // Version 10: Placement validation
    bool isValidCriterionPlacement(int id) const;
    bool isValidGoalPlacement(int id) const;

    // Version 8: resource distribution (prints only for now)
    void distributeRessources(int roll);

    // NEW version 10 accessors
    const std::vector<Tile>& getTiles() const;
    const std::vector<Criterion>& getCriteria() const;
    const std::vector<Goal>& getGoals() const;

    // Display
    void display(std::ostream& out) const;
    void print() const;

    friend std::ostream& operator<<(std::ostream& out, const Board& b);

private:
    int geeseTileIndex;

    // Tiles (19 hexes)
    std::vector<Tile> tiles;

    // 6 vertex indices per tile
    std::vector<std::vector<int>> tileCoords;

    // NEW in Version 10
    std::vector<Criterion> criteria;   // 54 vertices
    std::vector<Goal> goals;           // 72 edges

    // Helper adjacency logic
    bool adjacentCriterionExists(int id) const;
    bool adjacentGoalExists(int id) const;
};
