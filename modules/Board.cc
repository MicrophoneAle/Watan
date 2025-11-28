export module Board;

import <vector>;
import <array>;
import <iostream>;
import <map>;

import Tile;
import Criterion;
import Goal;
import WatanTypes;

using namespace std;

export class Board {
public:
    Board();

    // Setup
    void initializeTiles();
    void initializeGoalConnections();
    void placeGeese(int tileIndex);

    // Core accessors
    const vector<Tile>& getTiles() const;
    vector<Tile>& getTiles();

    const vector<Criterion>& getCriteria() const;
    vector<Criterion>& getCriteria();

    const vector<Goal>& getGoals() const;
    vector<Goal>& getGoals();

    int getGeeseTileIndex() const;

    // Validation
    bool isValidCriterionPlacement(int id, PlayerColour player, bool isInitialPlacement = false) const;
    bool isValidGoalPlacement(int id, PlayerColour player) const;
    bool isConnectedToPlayerGoal(int criterionId, PlayerColour player) const;

    // Adjacency helpers
    vector<int> getAdjacentCriteria(int criterionId) const;
    vector<int> getAdjacentGoals(int criterionId) const;
    vector<int> getCriteriaOnTile(int tileIndex) const;

    // Distribution
    void distributeResources(int roll, vector<pair<PlayerColour, vector<pair<ResourceType, int>>>>& gains);

    // Display
    void print() const;
    void display(ostream& out) const;
    string getCriterionDisplay(int id) const;
    string getGoalDisplay(int id) const;

private:
    vector<Tile> tiles;
    vector<Criterion> criteria;
    vector<Goal> goals;
    vector<std::array<int, 6>> tileCoords;
    map<int, pair<int, int>> goalConnections;
    int geeseTileIndex;

    // Adjacent helpers
    bool adjacentCriterionExists(int id) const;
};

export ostream& operator<<(ostream& out, const Board& b);
