export module Board;

import <vector>;
import <iostream>;
import <string>;
import Tile;
import WatanTypes;

export class Board {
private:
    int geeseTileIndex;

    // 19 tile objects
    std::vector<Tile> tiles;

    // 6 vertex neighbors for each tile
    std::vector<std::vector<int>> tileCoords;

public:
    Board(); // Constructor

    // Version 6 additions
    void initializeTiles();                   // Load 19 tiles
    void distributeRessources(int roll);      // Distribute based on dice roll

    // Geese system
    void placeGeese(int tileIndex);
    int getGeeseTileIndex() const;

    // Placeholder logic for future versions
    bool isValidCriterionPlacement(int criterionIndex);
    bool isValidGoalPlacement(int goalIndex);

    // Display
    void display(std::ostream& out) const;
    void print() const;

    friend std::ostream& operator<<(std::ostream& out, const Board& board);
};
