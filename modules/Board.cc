module Board;

import <iostream>;
import <vector>;
import <array>;
import <algorithm>;
import <map>;
import Tile;
import Criterion;
import Goal;
import WatanTypes;

// =============================
// Constructor
// =============================
Board::Board()
    : geeseTileIndex(4)  // Start on Netflix tile
{
    tiles.resize(19);
    criteria.resize(54);
    goals.resize(72);
    tileCoords.resize(19);

    for (int i = 0; i < 54; i++)
        criteria[i] = Criterion(i);

    for (int i = 0; i < 72; i++)
        goals[i] = Goal(i);

    // Tile coordinates mapping (criterion indices for each tile)
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

// =============================
// Tile Initialization
// =============================
void Board::initializeTiles() {
    std::vector<ResourceType> res = {
        ResourceType::Caffeine, // 0
        ResourceType::Lab,      // 1
        ResourceType::Study,    // 2
        ResourceType::Lab,      // 3
        ResourceType::Netflix,  // 4 (Start Geese Here)
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

    std::vector<int> vals = {
        3, 10, 5, 4, 7, 10, 11, 3, 8, 2, 6, 8, 12, 5, 11, 4, 6, 9, 9
    };

    for (int i = 0; i < 19; i++)
        tiles[i] = Tile(res[i], vals[i]);
}

// =============================
// Core Accessors
// =============================
const std::vector<Tile>& Board::getTiles() const { return tiles; }
std::vector<Tile>& Board::getTiles() { return tiles; }

const std::vector<Criterion>& Board::getCriteria() const { return criteria; }
std::vector<Criterion>& Board::getCriteria() { return criteria; }

const std::vector<Goal>& Board::getGoals() const { return goals; }
std::vector<Goal>& Board::getGoals() { return goals; }

int Board::getGeeseTileIndex() const { return geeseTileIndex; }

void Board::placeGeese(int idx) {
    if (idx >= 0 && idx < 19)
        geeseTileIndex = idx;
}

// =============================
// Helpers for Adjacency
// =============================
std::vector<int> Board::getAdjacentCriteria(int criterionId) const {
    std::vector<int> adjacent;

    // Criterion adjacency follows a pattern based on board structure
    // Each criterion can have up to 3 adjacent criteria
    int row = criterionId / 6;
    int col = criterionId % 6;

    // Left neighbor
    if (col > 0) adjacent.push_back(criterionId - 1);
    // Right neighbor
    if (col < 5) adjacent.push_back(criterionId + 1);
    // Vertical neighbors depend on position
    if (row > 0) adjacent.push_back(criterionId - 6);
    if (row < 8) adjacent.push_back(criterionId + 6);

    // Filter out invalid indices
    adjacent.erase(
        std::remove_if(adjacent.begin(), adjacent.end(),
            [](int id) { return id < 0 || id >= 54; }),
        adjacent.end()
    );

    return adjacent;
}

bool Board::adjacentCriterionExists(int id) const {
    auto adjacent = getAdjacentCriteria(id);
    for (int adjId : adjacent) {
        if (criteria[adjId].getOwner() != PlayerColour::None)
            return true;
    }
    return false;
}

bool Board::isValidCriterionPlacement(int id, PlayerColour player, bool isInitialPlacement) const {
    if (id < 0 || id >= 54) return false;
    if (criteria[id].getLevel() != 0) return false;

    // No adjacent criteria allowed (distance rule)
    if (adjacentCriterionExists(id)) return false;

    // During initial placement, any valid spot is OK
    if (isInitialPlacement) return true;

    // During game, must be connected to player's goal
    return isConnectedToPlayerGoal(id, player);
}

bool Board::isConnectedToPlayerGoal(int criterionId, PlayerColour player) const {
    // Check if any adjacent goal belongs to this player
    std::vector<int> adjacentGoals = getAdjacentGoals(criterionId);

    for (int goalId : adjacentGoals) {
        if (goalId >= 0 && goalId < 72 && goals[goalId].getOwner() == player) {
            return true;
        }
    }
    return false;
}

std::vector<int> Board::getAdjacentGoals(int criterionId) const {
    std::vector<int> adjacent;

    // Each criterion connects to 2-3 goals
    // Goals are numbered based on edges between criteria
    int baseGoal = criterionId * 2;

    if (baseGoal < 72) adjacent.push_back(baseGoal);
    if (baseGoal + 1 < 72) adjacent.push_back(baseGoal + 1);

    return adjacent;
}

bool Board::isValidGoalPlacement(int id, PlayerColour player) const {
    if (id < 0 || id >= 72) return false;
    if (goals[id].getOwner() != PlayerColour::None) return false;

    // Goal must be adjacent to player's criterion or goal
    int v1 = id / 2;
    int v2 = v1 + 1;

    if (v1 >= 0 && v1 < 54 && criteria[v1].getOwner() == player) return true;
    if (v2 >= 0 && v2 < 54 && criteria[v2].getOwner() == player) return true;

    // Check adjacent goals
    std::vector<int> adjGoals = { id - 1, id + 1, id - 6, id + 6 };
    for (int adjId : adjGoals) {
        if (adjId >= 0 && adjId < 72 && goals[adjId].getOwner() == player) {
            return true;
        }
    }

    return false;
}

// =============================
// Resource Distribution
// =============================
void Board::distributeResources(int roll, std::vector<std::pair<PlayerColour, std::vector<std::pair<ResourceType, int>>>>& gains) {
    gains.clear();

    if (roll == 7) {
        return; // Geese activated, no resources
    }

    // Track resources per player
    std::map<PlayerColour, std::vector<std::pair<ResourceType, int>>> playerGains;

    for (int tileIdx = 0; tileIdx < 19; tileIdx++) {
        if (tiles[tileIdx].getValue() == roll && tileIdx != geeseTileIndex) {
            ResourceType resource = tiles[tileIdx].getResource();

            if (resource == ResourceType::Netflix) continue;

            // Check each criterion on this tile
            const auto& criteriaOnTile = tileCoords[tileIdx];
            for (int critId : criteriaOnTile) {
                if (critId >= 0 && critId < 54) {
                    const Criterion& crit = criteria[critId];
                    if (crit.getLevel() > 0) {
                        PlayerColour owner = crit.getOwner();
                        int amount = crit.getLevel(); // 1=Assignment, 2=Midterm, 3=Exam

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

std::vector<int> Board::getCriteriaOnTile(int tileIndex) const {
    if (tileIndex < 0 || tileIndex >= 19) return {};
    return std::vector<int>(tileCoords[tileIndex].begin(), tileCoords[tileIndex].end());
}

// =============================
// Display with Criterion/Goal Ownership
// =============================
std::string Board::getCriterionDisplay(int id) const {
    if (id < 0 || id >= 54) return "??";

    const Criterion& crit = criteria[id];
    if (crit.getLevel() == 0) {
        return (id < 10 ? " " : "") + std::to_string(id);
    }

    // Show owner initial + level initial
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

    return std::string(1, owner) + std::string(1, level);
}

std::string Board::getGoalDisplay(int id) const {
    if (id < 0 || id >= 72) return "??";

    const Goal& goal = goals[id];
    if (goal.getOwner() == PlayerColour::None) {
        return (id < 10 ? " " : "") + std::to_string(id);
    }

    char owner = ' ';
    switch (goal.getOwner()) {
    case PlayerColour::Blue: owner = 'B'; break;
    case PlayerColour::Red: owner = 'R'; break;
    case PlayerColour::Orange: owner = 'O'; break;
    case PlayerColour::Yellow: owner = 'Y'; break;
    default: owner = '?'; break;
    }

    return std::string(1, owner) + "A"; // Achievement
}

void Board::display(std::ostream& out) const {
    auto c = [this](int i) { return "|" + getCriterionDisplay(i) + "|"; };
    auto h = [this](int i) { return "--" + getGoalDisplay(i) + "--"; };
    auto d = [this](int i) { return getGoalDisplay(i); };
    auto t = [](int i) { return (i < 10 ? " " : "") + std::to_string(i); };
    auto r = [&](int i) { return tiles[i].getResourceStr(); };
    auto v = [&](int i) {
        if (i == geeseTileIndex) return std::string(" GEESE");
        return tiles[i].getValueStr();
        };

    const std::string S1 = "   ";
    const std::string S2 = "                  ";
    const std::string S3 = "                                 ";

    out << "-----------------------------------------------------------------------------------------" << std::endl;

    // ROW 0 (Tip)
    out << S3 << "  " << c(0) << h(0) << c(1) << std::endl;
    out << S3 << "  /            \\" << std::endl;
    out << S3 << d(1) << "      " << t(0) << "     " << d(2) << std::endl;
    out << S3 << "/    " << r(0) << "    \\" << std::endl;

    // ROW 1
    out << S2 << "  " << c(2) << h(3) << c(3) << "       " << v(0) << "       " << c(4) << h(4) << c(5) << std::endl;
    out << S2 << "  /            \\                /            \\" << std::endl;
    out << S2 << d(5) << "      " << t(1) << "     " << d(6) << "             " << d(7) << "      " << t(2) << "     " << d(8) << std::endl;
    out << S2 << "/    " << r(1) << "    \\            /    " << r(2) << "    \\" << std::endl;

    // ROW 2
    out << S1 << "  " << c(6) << h(9) << c(7) << "       " << v(1) << "       " << c(8) << h(10) << c(9) << "       " << v(2) << "       " << c(10) << h(11) << c(11) << std::endl;
    out << S1 << "  /            \\                /            \\                /            \\" << std::endl;
    out << S1 << d(12) << "      " << t(3) << "     " << d(13) << "             " << d(14) << "      " << t(4) << "     " << d(15) << "             " << d(16) << "      " << t(5) << "     " << d(17) << std::endl;
    out << S1 << "/    " << r(3) << "    \\            /    " << r(4) << "    \\            /    " << r(5) << "    \\" << std::endl;

    // ROW 3 - FIXED: was r(0), r(0) - should be r(6), r(7)
    out << c(12) << "       " << v(3) << "       " << c(13) << h(18) << c(14) << "       " << v(4) << "       " << c(15) << h(19) << c(16) << "       " << v(5) << "       " << c(17) << std::endl;
    out << "   \\                /            \\                /            \\                /" << std::endl;
    out << "   " << d(20) << "             " << d(21) << "      " << t(6) << "     " << d(22) << "             " << d(23) << "      " << t(7) << "     " << d(24) << "             " << d(25) << std::endl;
    out << "     \\            /    " << r(6) << "    \\            /    " << r(7) << "    \\            /" << std::endl;

    // ROW 4
    out << S1 << "  " << c(18) << h(26) << c(19) << "       " << v(6) << "       " << c(20) << h(27) << c(21) << "       " << v(7) << "       " << c(22) << h(28) << c(23) << std::endl;
    out << S1 << "  /            \\                /            \\                /            \\" << std::endl;
    out << S1 << d(29) << "      " << t(8) << "     " << d(30) << "             " << d(31) << "      " << t(9) << "     " << d(32) << "             " << d(33) << "      " << t(10) << "     " << d(34) << std::endl;
    out << S1 << "/    " << r(8) << "    \\            /    " << r(9) << "    \\            /    " << r(10) << "    \\" << std::endl;

    // ROW 5
    out << c(24) << "       " << v(8) << "       " << c(25) << h(35) << c(26) << "       " << v(9) << "       " << c(27) << h(36) << c(28) << "       " << v(10) << "       " << c(29) << std::endl;
    out << "   \\                /            \\                /            \\                /" << std::endl;
    out << "   " << d(37) << "             " << d(38) << "      " << t(11) << "     " << d(39) << "             " << d(40) << "      " << t(12) << "     " << d(41) << "             " << d(42) << std::endl;
    out << "     \\            /    " << r(11) << "    \\            /    " << r(12) << "    \\            /" << std::endl;

    // ROW 6
    out << S1 << "  " << c(30) << h(43) << c(31) << "       " << v(11) << "       " << c(32) << h(44) << c(33) << "       " << v(12) << "       " << c(34) << h(45) << c(35) << std::endl;
    out << S1 << "  /            \\                /            \\                /            \\" << std::endl;
    out << S1 << d(46) << "      " << t(13) << "     " << d(47) << "             " << d(48) << "      " << t(14) << "     " << d(49) << "             " << d(50) << "      " << t(15) << "     " << d(51) << std::endl;
    out << S1 << "/    " << r(13) << "    \\            /    " << r(14) << "    \\            /    " << r(15) << "    \\" << std::endl;

    // ROW 7 - FIXED: was r(12), r(13) - should be r(16), r(17)
    out << c(36) << "       " << v(13) << "       " << c(37) << h(52) << c(38) << "       " << v(14) << "       " << c(39) << h(53) << c(40) << "       " << v(15) << "       " << c(41) << std::endl;
    out << "   \\                /            \\                /            \\                /" << std::endl;
    out << "   " << d(54) << "             " << d(55) << "      " << t(16) << "     " << d(56) << "             " << d(57) << "      " << t(17) << "     " << d(58) << "             " << d(59) << std::endl;
    out << "     \\            /    " << r(16) << "    \\            /    " << r(17) << "    \\            /" << std::endl;

    // ROW 8 - FIXED: was r(15) - should be r(18)
    out << S1 << "  " << c(42) << h(60) << c(43) << "       " << v(16) << "       " << c(44) << h(61) << c(45) << "       " << v(17) << "       " << c(46) << h(62) << c(47) << std::endl;
    out << S2 << "\\                /            \\                /" << std::endl;
    out << S2 << d(63) << "             " << d(64) << "      " << t(18) << "     " << d(65) << "             " << d(66) << std::endl;
    out << S2 << "  \\            /    " << r(18) << "    \\            / " << std::endl;

    // ROW 9 (Tip)
    out << S2 << "  " << c(48) << h(67) << c(49) << "       " << v(18) << "       " << c(50) << h(68) << c(51) << std::endl;
    out << S3 << "\\                /" << std::endl;
    out << S3 << d(69) << "             " << d(70) << std::endl;
    out << S3 << "  \\            /" << std::endl;
    out << S3 << "  " << c(52) << h(71) << c(53) << std::endl;
    out << "-----------------------------------------------------------------------------------------" << std::endl;
}

void Board::print() const { display(std::cout); }

std::ostream& operator<<(std::ostream& out, const Board& board) {
    board.display(out);
    return out;
}