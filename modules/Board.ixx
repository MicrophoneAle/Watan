export module Board;

import <vector>;
import <iostream>;
import <string>;

/*
import Tile;
import Criterion;
import Goal;
*/

// Import the module defining Resource/ResourceType if needed for Resource::NONE
//import resource_type; 

export class Board {
private:
    //std::vector<Tile> tiles;
    //std::vector<Criterion> criteria;
    //std::vector<Goal> goals;
    int geeseTileIndex;

    // This holds the 6 vertex neighbors for every tile (0 to 18)
    std::vector<std::vector<int>> tileCoords;

public:
    Board(); // Constructor Declaration

    void initializeTiles();
    void placeGeese(int tileIndex);
    int getGeeseTileIndex() const;

    bool isValidCriterionPlacement(int criterionIndex);
    bool isValidGoalPlacement(int goalIndex);
    void distributeRessources(int roll);

    void display(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const Board& board);
};
