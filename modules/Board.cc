module Board;

import <iostream>;
import <vector>;
import <array>;
import <map>;
import Tile;
import Criterion;
import Goal;
import WatanTypes;

using namespace std;

// Board constructor
Board::Board() : geeseTileIndex(4) { // Geese start on netflix tile
    tiles.resize(19);
    criteria.resize(54);
    goals.resize(72);
    tileCoords.resize(19);
    initializeGoalConnections();

    for (int i = 0; i < 54; i++) {
        criteria[i] = Criterion(i);
    }

    for (int i = 0; i < 72; i++) {
        goals[i] = Goal(i);
    }

    // Tile coordinates mapping
    tileCoords[0] = { 0,1,4,9,8,3 };
    tileCoords[1] = { 2,3,8,14,13,7 };
    tileCoords[2] = { 4,5,10,16,15,9 };

    tileCoords[3] = { 6,7,13,19,18,12 };
    tileCoords[4] = { 8,9,15,21,20,14 };
    tileCoords[5] = { 10,11,17,23,22,16 };

    tileCoords[6] = { 13,14,20,26,25,19 };
    tileCoords[7] = { 15,16,22,28,27,21 };

    tileCoords[8] = { 18,19,25,31,30,24 };
    tileCoords[9] = { 20,21,27,33,32,26 };
    tileCoords[10] = { 22,23,29,35,34,28 };

    tileCoords[11] = { 25,26,32,38,37,31 };
    tileCoords[12] = { 27,28,34,40,39,33 };

    tileCoords[13] = { 30,31,37,43,42,36 };
    tileCoords[14] = { 32,33,39,45,44,38 };
    tileCoords[15] = { 34,35,41,47,46,40 };

    tileCoords[16] = { 37,38,44,49,48,43 };
    tileCoords[17] = { 39,40,46,51,50,45 };

    tileCoords[18] = { 44,45,50,53,52,49 };

    initializeTiles();
}

// Initialize the goal connection mapping based on tile structure
// Each tile is a hexagon with 6 edges connecting its 6 vertices
void Board::initializeGoalConnections() {
    goalConnections.clear();

    // Extracted from tile coordinates - each tile has 6 vertices that form edges
    // These are the correct connections based on the actual hexagonal structure

    goalConnections[0] = { 0, 1 };
    goalConnections[1] = { 0, 3 };
    goalConnections[2] = { 1, 4 };
    goalConnections[3] = { 2, 3 };
    goalConnections[4] = { 2, 7 };
    goalConnections[5] = { 3, 8 };
    goalConnections[6] = { 4, 5 };
    goalConnections[7] = { 4, 9 };
    goalConnections[8] = { 5, 10 };
    goalConnections[9] = { 6, 7 };
    goalConnections[10] = { 6, 12 };
    goalConnections[11] = { 7, 13 };
    goalConnections[12] = { 8, 9 };
    goalConnections[13] = { 8, 14 };
    goalConnections[14] = { 9, 15 };
    goalConnections[15] = { 10, 11 };
    goalConnections[16] = { 10, 16 };
    goalConnections[17] = { 11, 17 };
    goalConnections[18] = { 12, 18 };
    goalConnections[19] = { 13, 14 };
    goalConnections[20] = { 13, 19 };
    goalConnections[21] = { 14, 20 };
    goalConnections[22] = { 15, 16 };
    goalConnections[23] = { 15, 21 };
    goalConnections[24] = { 16, 22 };
    goalConnections[25] = { 17, 23 };
    goalConnections[26] = { 18, 19 };
    goalConnections[27] = { 18, 24 };
    goalConnections[28] = { 19, 25 };
    goalConnections[29] = { 20, 21 };
    goalConnections[30] = { 20, 26 };
    goalConnections[31] = { 21, 27 };
    goalConnections[32] = { 22, 23 };
    goalConnections[33] = { 22, 28 };
    goalConnections[34] = { 23, 29 };
    goalConnections[35] = { 24, 30 };
    goalConnections[36] = { 25, 26 };
    goalConnections[37] = { 25, 31 };
    goalConnections[38] = { 26, 32 };
    goalConnections[39] = { 27, 28 };
    goalConnections[40] = { 27, 33 };
    goalConnections[41] = { 28, 34 };
    goalConnections[42] = { 29, 35 };
    goalConnections[43] = { 30, 31 };
    goalConnections[44] = { 30, 36 };
    goalConnections[45] = { 31, 37 };
    goalConnections[46] = { 32, 33 };
    goalConnections[47] = { 32, 38 };
    goalConnections[48] = { 33, 39 };
    goalConnections[49] = { 34, 35 };
    goalConnections[50] = { 34, 40 };
    goalConnections[51] = { 35, 41 };
    goalConnections[52] = { 36, 42 };
    goalConnections[53] = { 37, 38 };
    goalConnections[54] = { 37, 43 };
    goalConnections[55] = { 38, 44 };
    goalConnections[56] = { 39, 40 };
    goalConnections[57] = { 39, 45 };
    goalConnections[58] = { 40, 46 };
    goalConnections[59] = { 41, 47 };
    goalConnections[60] = { 42, 43 };
    goalConnections[61] = { 43, 48 };
    goalConnections[62] = { 44, 45 };
    goalConnections[63] = { 44, 49 };
    goalConnections[64] = { 45, 50 };
    goalConnections[65] = { 46, 47 };
    goalConnections[66] = { 46, 51 };
    goalConnections[67] = { 48, 49 };
    goalConnections[68] = { 49, 52 };
    goalConnections[69] = { 50, 51 };
    goalConnections[70] = { 50, 53 };
    goalConnections[71] = { 52, 53 };
}

// Tile initialization
void Board::initializeTiles() {
    vector<ResourceType> res = {
        ResourceType::Caffeine, // 0
        ResourceType::Lab,      // 1
        ResourceType::Study,    // 2
        ResourceType::Lab,      // 3
        ResourceType::Netflix,  // 4
        ResourceType::Study,    // 5
        ResourceType::Lecture,  // 6
        ResourceType::Caffeine, // 7
        ResourceType::Study,    // 8
        ResourceType::Caffeine, // 9
        ResourceType::Caffeine, // 10
        ResourceType::Lab,      // 11
        ResourceType::Tutorial, // 12
        ResourceType::Lab,      // 13
        ResourceType::Tutorial, // 14
        ResourceType::Lecture,  // 15
        ResourceType::Tutorial, // 16
        ResourceType::Lecture,  // 17
        ResourceType::Lecture   // 18
    };

    vector<int> vals = {
        3, 10, 5, 4, 7, 10, 11, 3, 8, 2, 6, 8, 12, 5, 11, 4, 6, 9, 9
    };

    for (int i = 0; i < 19; i++) {
        tiles[i] = Tile(res[i], vals[i]);
    }
}

// Core accessors
const vector<Tile>& Board::getTiles() const { return tiles; }
vector<Tile>& Board::getTiles() { return tiles; }

const vector<Criterion>& Board::getCriteria() const { return criteria; }
vector<Criterion>& Board::getCriteria() { return criteria; }

const vector<Goal>& Board::getGoals() const { return goals; }
vector<Goal>& Board::getGoals() { return goals; }

int Board::getGeeseTileIndex() const { return geeseTileIndex; }

void Board::placeGeese(int idx) {
    // Checking if geese placement is valid
    if (idx >= 0 && idx < 19) {
        geeseTileIndex = idx;
    }
}

// CORRECT adjacency based on goal connections
vector<int> Board::getAdjacentCriteria(int criterionId) const {
    vector<int> adjacent;

    if (criterionId < 0 || criterionId >= 54) {
        return adjacent;
    }

    // Check all goals to see which ones connect to this criterion
    for (const auto& [goalId, criteria] : goalConnections) {
        int otherCriterion = -1;

        if (criteria.first == criterionId) {
            otherCriterion = criteria.second;
        }
        else if (criteria.second == criterionId) {
            otherCriterion = criteria.first;
        }

        if (otherCriterion != -1) {
            // Check if already in adjacent list
            bool found = false;
            for (int adj : adjacent) {
                if (adj == otherCriterion) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                adjacent.push_back(otherCriterion);
            }
        }
    }

    return adjacent;
}

bool Board::adjacentCriterionExists(int id) const {
    auto adjacent = getAdjacentCriteria(id);

    for (int adjId : adjacent) {
        if (adjId >= 0 && adjId < 54 && criteria[adjId].getOwner() != PlayerColour::None) {
            return true;
        }
    }
    return false;
}

bool Board::isValidCriterionPlacement(int id, PlayerColour player, bool isInitialPlacement) const {
    if (id < 0 || id >= 54) {
        return false;
    }
    if (criteria[id].getLevel() != 0) {
        return false;
    }

    // Check for adjacent criteria
    if (adjacentCriterionExists(id)) {
        return false;
    }

    // First placement
    if (isInitialPlacement) {
        return true;
    }

    // Check if connected to goal
    return isConnectedToPlayerGoal(id, player);
}

bool Board::isConnectedToPlayerGoal(int criterionId, PlayerColour player) const {
    // Check all goals to see if any connect this criterion and belong to the player
    for (const auto& [goalId, criteria] : goalConnections) {
        if ((criteria.first == criterionId || criteria.second == criterionId) &&
            goalId >= 0 && goalId < 72 && goals[goalId].getOwner() == player) {
            return true;
        }
    }
    return false;
}

vector<int> Board::getAdjacentGoals(int criterionId) const {
    vector<int> adjacent;

    // Find all goals that connect to this criterion
    for (const auto& [goalId, criteria] : goalConnections) {
        if (criteria.first == criterionId || criteria.second == criterionId) {
            adjacent.push_back(goalId);
        }
    }

    return adjacent;
}

bool Board::isValidGoalPlacement(int id, PlayerColour player) const {
    if (id < 0 || id >= 72) {
        return false;
    }
    if (goals[id].getOwner() != PlayerColour::None) {
        return false;
    }

    // Goal must be adjacent to player's criterion or goal
    // Check if either endpoint criterion belongs to the player
    auto it = goalConnections.find(id);
    if (it != goalConnections.end()) {
        int v1 = it->second.first;
        int v2 = it->second.second;

        if (v1 >= 0 && v1 < 54 && criteria[v1].getOwner() == player) {
            return true;
        }
        if (v2 >= 0 && v2 < 54 && criteria[v2].getOwner() == player) {
            return true;
        }
    }

    // Check if connected to another goal owned by player
    // A goal is adjacent to another goal if they share a criterion endpoint
    if (it != goalConnections.end()) {
        for (const auto& [otherGoalId, otherCriteria] : goalConnections) {
            if (otherGoalId != id && goals[otherGoalId].getOwner() == player) {
                // Check if they share a criterion
                if (it->second.first == otherCriteria.first ||
                    it->second.first == otherCriteria.second ||
                    it->second.second == otherCriteria.first ||
                    it->second.second == otherCriteria.second) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Resource distribution functions
void Board::distributeResources(int roll, vector<pair<PlayerColour, vector<pair<ResourceType, int>>>>& gains) {
    gains.clear();

    if (roll == 7) {
        return; // Geese activated, no resources
    }

    // Track resources per player
    map<PlayerColour, vector<pair<ResourceType, int>>> playerGains;

    for (int tileIdx = 0; tileIdx < 19; tileIdx++) {
        if (tiles[tileIdx].getValue() == roll && tileIdx != geeseTileIndex) {
            ResourceType resource = tiles[tileIdx].getResource();

            if (resource == ResourceType::Netflix) {
                continue;
            }

            // Check the criterion on this tile
            const auto& criteriaOnTile = tileCoords[tileIdx];

            for (int critId : criteriaOnTile) {
                if (critId >= 0 && critId < 54) {
                    const Criterion& crit = criteria[critId];

                    if (crit.getLevel() > 0) {
                        PlayerColour owner = crit.getOwner();
                        int amount = crit.getLevel();
                        playerGains[owner].push_back({ resource, amount });
                    }
                }
            }
        }
    }

    // Convert map to vector
    for (const auto& [player, resources] : playerGains) {
        gains.push_back({ player, resources });
    }
}

vector<int> Board::getCriteriaOnTile(int tileIndex) const {
    if (tileIndex < 0 || tileIndex >= 19) {
        return {};
    }
    return std::vector<int>(tileCoords[tileIndex].begin(), tileCoords[tileIndex].end());
}

// Put ownership of goals and critiea into display strings
string Board::getCriterionDisplay(int id) const {
    if (id < 0 || id >= 54) {
        return "??";
    }

    const Criterion& crit = criteria[id];

    if (crit.getLevel() == 0) {
        return (id < 10 ? " " : "") + std::to_string(id);
    }

    // Show owner initials and level initials
    char owner = ' ';

    switch (crit.getOwner()) {
    case PlayerColour::Blue: owner = 'B'; break;
    case PlayerColour::Red: owner = 'R'; break;
    case PlayerColour::Orange: owner = 'O'; break;
    case PlayerColour::Yellow: owner = 'Y'; break;
    default: owner = '?'; break;
    }

    char level = ' ';

    switch (crit.getLevel()) {
    case 1: level = 'A'; break; // Assignment
    case 2: level = 'M'; break; // Midterm
    case 3: level = 'E'; break; // Exam
    default: level = '?'; break;
    }
    return string(1, owner) + string(1, level);
}

string Board::getGoalDisplay(int id) const {
    if (id < 0 || id >= 72) {
        return "??";
    }

    const Goal& goal = goals[id];

    if (goal.getOwner() == PlayerColour::None) {
        return (id < 10 ? " " : "") + to_string(id);
    }

    char owner = ' ';

    switch (goal.getOwner()) {
    case PlayerColour::Blue: owner = 'B'; break;
    case PlayerColour::Red: owner = 'R'; break;
    case PlayerColour::Orange: owner = 'O'; break;
    case PlayerColour::Yellow: owner = 'Y'; break;
    default: owner = '?'; break;
    }

    return string(1, owner) + "A"; // Achievement
}

void Board::display(ostream& out) const {
    auto c = [this](int i) { return "|" + getCriterionDisplay(i) + "|"; };
    auto h = [this](int i) { return "--" + getGoalDisplay(i) + "--"; };
    auto d = [this](int i) { return getGoalDisplay(i); };
    auto t = [](int i) { return (i < 10 ? " " : "") + std::to_string(i); };
    auto r = [&](int i) { return tiles[i].getResourceStr(); };
    auto v = [&](int i) {
        if (i == geeseTileIndex) return std::string(" GE");
        return tiles[i].getValueStr();
        };

    const std::string S1 = "   ";
    const std::string S2 = "                  ";
    const std::string S3 = "                                 ";

    out << "-----------------------------------------------------------------------------------------" << endl;

    // ROW 0 (Tip)
    out << S3 << "  " << c(0) << h(0) << c(1) << endl;
    out << S3 << "  /            \\" << endl;
    out << S3 << d(1) << "      " << t(0) << "     " << d(2) << endl;
    out << S3 << "/    " << r(0) << "    \\" << endl;

    // ROW 1
    out << S2 << "  " << c(2) << h(3) << c(3) << "       " << v(0) << "       " << c(4) << h(4) << c(5) << endl;
    out << S2 << "  /            \\                /            \\" << endl;
    out << S2 << d(5) << "      " << t(1) << "     " << d(6) << "             " << d(7) << "      " << t(2) << "     " << d(8) << endl;
    out << S2 << "/    " << r(1) << "    \\            /    " << r(2) << "    \\" << endl;

    // ROW 2
    out << S1 << "  " << c(6) << h(9) << c(7) << "       " << v(1) << "       " << c(8) << h(10) << c(9) << "       " << v(2) << "       " << c(10) << h(11) << c(11) << endl;
    out << S1 << "  /            \\                /            \\                /            \\" << endl;
    out << S1 << d(12) << "      " << t(3) << "     " << d(13) << "             " << d(14) << "      " << t(4) << "     " << d(15) << "             " << d(16) << "      " << t(5) << "     " << d(17) << endl;
    out << S1 << "/    " << r(3) << "    \\            /    " << r(4) << "    \\            /    " << r(5) << "    \\" << endl;

    // ROW 3
    out << c(12) << "       " << v(3) << "       " << c(13) << h(18) << c(14) << "       " << v(4) << "       " << c(15) << h(19) << c(16) << "       " << v(5) << "       " << c(17) << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << d(20) << "             " << d(21) << "      " << t(6) << "     " << d(22) << "             " << d(23) << "      " << t(7) << "     " << d(24) << "             " << d(25) << endl;
    out << "     \\            /    " << r(6) << "    \\            /    " << r(7) << "    \\            /" << endl;

    // ROW 4
    out << S1 << "  " << c(18) << h(26) << c(19) << "       " << v(6) << "       " << c(20) << h(27) << c(21) << "       " << v(7) << "       " << c(22) << h(28) << c(23) << endl;
    out << S1 << "  /            \\                /            \\                /            \\" << endl;
    out << S1 << d(29) << "      " << t(8) << "     " << d(30) << "             " << d(31) << "      " << t(9) << "     " << d(32) << "             " << d(33) << "      " << t(10) << "     " << d(34) << endl;
    out << S1 << "/    " << r(8) << "    \\            /    " << r(9) << "    \\            /    " << r(10) << "    \\" << endl;

    // ROW 5
    out << c(24) << "       " << v(8) << "       " << c(25) << h(35) << c(26) << "       " << v(9) << "       " << c(27) << h(36) << c(28) << "       " << v(10) << "       " << c(29) << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << d(37) << "             " << d(38) << "      " << t(11) << "     " << d(39) << "             " << d(40) << "      " << t(12) << "     " << d(41) << "             " << d(42) << endl;
    out << "     \\            /    " << r(11) << "    \\            /    " << r(12) << "    \\            /" << endl;

    // ROW 6
    out << S1 << "  " << c(30) << h(43) << c(31) << "       " << v(11) << "       " << c(32) << h(44) << c(33) << "       " << v(12) << "       " << c(34) << h(45) << c(35) << endl;
    out << S1 << "  /            \\                /            \\                /            \\" << endl;
    out << S1 << d(46) << "      " << t(13) << "     " << d(47) << "             " << d(48) << "      " << t(14) << "     " << d(49) << "             " << d(50) << "      " << t(15) << "     " << d(51) << endl;
    out << S1 << "/    " << r(13) << "    \\            /    " << r(14) << "    \\            /    " << r(15) << "    \\" << endl;

    // ROW 7
    out << c(36) << "       " << v(13) << "       " << c(37) << h(52) << c(38) << "       " << v(14) << "       " << c(39) << h(53) << c(40) << "       " << v(15) << "       " << c(41) << endl;
    out << "   \\                /            \\                /            \\                /" << endl;
    out << "   " << d(54) << "             " << d(55) << "      " << t(16) << "     " << d(56) << "             " << d(57) << "      " << t(17) << "     " << d(58) << "             " << d(59) << endl;
    out << "     \\            /    " << r(16) << "    \\            /    " << r(17) << "    \\            /" << endl;

    // ROW 8
    out << S1 << "  " << c(42) << h(60) << c(43) << "       " << v(16) << "       " << c(44) << h(61) << c(45) << "       " << v(17) << "       " << c(46) << h(62) << c(47) << endl;
    out << S2 << "\\                /            \\                /" << endl;
    out << S2 << d(63) << "             " << d(64) << "      " << t(18) << "     " << d(65) << "             " << d(66) << endl;
    out << S2 << "  \\            /    " << r(18) << "    \\            / " << endl;

    // ROW 9 (Tip)
    out << S2 << "  " << c(48) << h(67) << c(49) << "       " << v(18) << "       " << c(50) << h(68) << c(51) << endl;
    out << S3 << "\\                /" << endl;
    out << S3 << d(69) << "             " << d(70) << endl;
    out << S3 << "  \\            /" << endl;
    out << S3 << "  " << c(52) << h(71) << c(53) << endl;
    out << "-----------------------------------------------------------------------------------------" << endl;
}

void Board::print() const { display(cout); }

ostream& operator<<(ostream& out, const Board& board) {
    board.display(out);
    return out;
}
