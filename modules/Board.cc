// ===== Board.cc =====
module Board;

import <array>;
import <vector>;
import <iostream>;
import <string>;
import Tile;
import Criterion;
import Goal;
import WatanTypes;

// --------------------------------------------------------------------------
// Constructor & Setup
// --------------------------------------------------------------------------
Board::Board()
    : geeseTileIndex{ -1 }
{
    // Allocate containers
    tiles.resize(19);
    criteria.resize(54);
    goals.resize(72);
    tileCoords.resize(19);

    // Initialize criteria & goals with ids; adjacency will be wired later.
    for (int i = 0; i < 54; ++i) {
        criteria[i] = Criterion(i);
    }
    for (int i = 0; i < 72; ++i) {
        goals[i] = Goal(i);
    }

    // ---------------------------------------------------------
    // 6 vertex numbers starting from top-left, going clockwise
    // These indices come directly from the assignment board diagram.
    // tileCoords[tile] = { six criterion indices around that tile }
    // ---------------------------------------------------------

    // Row 1 (Top)
    tileCoords[0] = { 0, 1, 4, 9, 8, 3 };

    // Row 2
    tileCoords[1] = { 2, 3, 8, 14, 13, 7 };
    tileCoords[2] = { 4, 5, 10, 16, 15, 9 };

    // Row 3
    tileCoords[3] = { 6, 7, 13, 19, 18, 12 };
    tileCoords[4] = { 8, 9, 15, 21, 20, 14 };
    tileCoords[5] = { 10, 11, 17, 23, 22, 16 };

    // Row 4
    tileCoords[6] = { 13, 14, 20, 26, 25, 19 };
    tileCoords[7] = { 15, 16, 22, 28, 27, 21 };

    // Row 5
    tileCoords[8] = { 18, 19, 25, 31, 30, 24 };
    tileCoords[9] = { 20, 21, 27, 33, 32, 26 };
    tileCoords[10] = { 22, 23, 29, 35, 34, 28 };

    // Row 6
    tileCoords[11] = { 25, 26, 32, 38, 37, 31 };
    tileCoords[12] = { 27, 28, 34, 40, 39, 33 };

    // Row 7
    tileCoords[13] = { 30, 31, 37, 43, 42, 36 };
    tileCoords[14] = { 32, 33, 39, 45, 44, 38 };
    tileCoords[15] = { 34, 35, 41, 47, 46, 40 };

    // Row 8
    tileCoords[16] = { 37, 38, 44, 49, 48, 43 };
    tileCoords[17] = { 39, 40, 46, 51, 50, 45 };

    // Row 9 (Bottom)
    tileCoords[18] = { 44, 45, 50, 53, 52, 49 };
}

// --------------------------------------------------------------------------
// Logic Methods
// --------------------------------------------------------------------------

void Board::initializeTiles() {
    // These can be randomized in a later version (RandomBoardSetupStrategy).
    std::vector<ResourceType> resources = {
        ResourceType::Caffeine, ResourceType::Study,    ResourceType::Lecture,
        ResourceType::Lab,      ResourceType::Tutorial, ResourceType::Caffeine,
        ResourceType::Study,    ResourceType::Lecture,  ResourceType::Lab,
        ResourceType::Tutorial, ResourceType::Caffeine, ResourceType::Study,
        ResourceType::Lecture,  ResourceType::Lab,      ResourceType::Tutorial,
        ResourceType::Caffeine, ResourceType::Study,    ResourceType::Lecture,
        ResourceType::Netflix   // Geese tile
    };

    std::vector<int> values = {
        4, 6, 9, 5, 8, 10, 3, 11, 12, 2,
        4, 6, 9, 5, 8, 10, 3, 11, 7
    };

    // Make sure we actually have 19 tiles allocated (done in ctor).
    for (int i = 0; i < 19; ++i) {
        tiles[i] = Tile(resources[i], values[i]);
    }
}

void Board::placeGeese(int tileIndex) {
    if (tileIndex >= 0 && tileIndex < static_cast<int>(tiles.size())) {
        geeseTileIndex = tileIndex;
    }
}

int Board::getGeeseTileIndex() const {
    return geeseTileIndex;
}

bool Board::adjacentCriterionExists(int id) const {
    // Criterion graph:
    // each vertex has up to 3 neighbors in typical Catan geometry
    // Formula from UML: neighbors = { id-1, id+1, id±6 }
    // (wraps must be checked)
    static const int offsets[4] = { -1, +1, -6, +6 };

    for (int d : offsets) {
        int n = id + d;
        if (n >= 0 && n < 54) {
            if (criteria[n].getOwner() != PlayerColour::Blue)
                return true;
        }
    }
    return false;
}

bool Board::isValidCriterionPlacement(int id) const {
    if (id < 0 || id >= 54) return false;

    const Criterion& c = criteria[id];
    if (c.getLevel() != 0) return false;        // already owned

    // must not be next to another criterion
    if (adjacentCriterionExists(id)) return false;

    return true;
}

// --------------------

bool Board::adjacentGoalExists(int id) const {
    // From UML: each edge touches two vertices => two adjacent goals
    // Approx formula: neighbors ≈ id±1 (same row) and id±6 (row above/below)

    static const int offsets[4] = { -1, +1, -6, +6 };

    for (int d : offsets) {
        int n = id + d;
        if (n >= 0 && n < 72) {
            if (goals[n].getOwner() != PlayerColour::Blue)
                return true;
        }
    }
    return false;
}

bool Board::isValidGoalPlacement(int id) const {
    if (id < 0 || id >= 72) return false;

    const Goal& g = goals[id];
    if (g.getOwner() != PlayerColour::Blue) return false;

    // Must connect to at least one owned criterion
    // Simplified from UML:
    int v1 = id / 2;
    int v2 = v1 + 1;
    if (v1 >= 0 && v1 < 54 && criteria[v1].getLevel() > 0) return true;
    if (v2 >= 0 && v2 < 54 && criteria[v2].getLevel() > 0) return true;

    return false;
}

void Board::distributeRessources(int roll) {
    if (roll == 7) {
        std::cout << "[Board] Roll = 7 - Geese activated!\n";
        return;
    }

    // Version 8: keep behaviour simple (just print which tiles would produce).
    // In a later version we will:
    //   - walk tileCoords
    //   - check which criteria are owned and at what level (Assignment/Midterm/Exam)
    //   - actually credit resources to players
    for (int i = 0; i < 19; i++) {
        if (tiles[i].getValue() == roll && i != geeseTileIndex) {
            std::cout << "Tile " << i
                << " produced " << toString(tiles[i].getResource())
                << "\n";
        }
    }
}

// --------------------------------------------------------------------------
// Accessors
// --------------------------------------------------------------------------

const std::vector<Tile>& Board::getTiles() const {
    return tiles;
}

const std::vector<Criterion>& Board::getCriteria() const {
    return criteria;
}

const std::vector<Goal>& Board::getGoals() const {
    return goals;
}

// --------------------------------------------------------------------------
// Display Logic (unchanged from your version)
// --------------------------------------------------------------------------

void Board::display(std::ostream& out) const {
    if (tileCoords.empty()) {
        out << "Board not initialized." << std::endl;
        return;
    }

    auto fmt = [](int i) { return (i < 10 ? " " : "") + std::to_string(i); };
    auto c = [fmt](int i) { return "|" + fmt(i) + "|"; };       // CENTER NUMBERS
    auto h = [fmt](int i) { return "--" + fmt(i) + "--"; };     // HORIZONTAL NUMBERS
    auto d = [fmt](int i) { return fmt(i); };                   //
    auto t = [fmt](int i) { return fmt(i); };                   // TILE NUMBERS
    auto r = [](int) { return "CAFFEINE"; };                    // RESOURCE NAMES (placeholder)
    auto v = [](int) { return "XX"; };                          // DICE NUMBERS (placeholder)

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

    // ROW 3 (Leftmost)
    out << c(12) << "       " << v(0) << "       " << c(13) << h(18) << c(14) << "       " << v(4) << "       " << c(15) << h(19) << c(16) << "       " << v(5) << "       " << c(17) << std::endl;
    out << "   \\                /            \\                /            \\                /" << std::endl;
    out << "   " << d(20) << "             " << d(21) << "      " << t(6) << "     " << d(22) << "             " << d(23) << "      " << t(7) << "     " << d(24) << "             " << d(25) << std::endl;
    out << "     \\            /    " << r(0) << "    \\            /    " << r(0) << "    \\            /" << std::endl;

    // ROW 4
    out << S1 << "  " << c(18) << h(26) << c(19) << "       " << v(6) << "       " << c(20) << h(27) << c(21) << "       " << v(7) << "       " << c(22) << h(28) << c(23) << std::endl;
    out << S1 << "  /            \\                /            \\                /            \\" << std::endl;
    out << S1 << d(29) << "      " << t(8) << "     " << d(30) << "             " << d(31) << "      " << t(9) << "     " << d(32) << "             " << d(33) << "      " << t(10) << "     " << d(34) << std::endl;
    out << S1 << "/    " << r(9) << "    \\            /    " << r(10) << "    \\            /    " << r(11) << "    \\" << std::endl;

    // ROW 5 (Leftmost)
    out << c(24) << "       " << v(12) << "       " << c(25) << h(35) << c(26) << "       " << v(13) << "       " << c(27) << h(36) << c(28) << "       " << v(14) << "       " << c(29) << std::endl;
    out << "   \\                /            \\                /            \\                /" << std::endl;
    out << "   " << d(37) << "             " << d(38) << "      " << t(11) << "     " << d(39) << "             " << d(40) << "      " << t(12) << "     " << d(41) << "             " << d(42) << std::endl;
    out << "     \\            /    " << r(12) << "    \\            /    " << r(13) << "    \\            /" << std::endl;

    // ROW 6 
    out << S1 << "  " << c(30) << h(43) << c(31) << "       " << v(15) << "       " << c(32) << h(44) << c(33) << "       " << v(16) << "       " << c(34) << h(45) << c(35) << std::endl;
    out << S1 << "  /            \\                /            \\                /            \\" << std::endl;
    out << S1 << d(46) << "      " << t(13) << "     " << d(47) << "             " << d(48) << "      " << t(14) << "     " << d(49) << "             " << d(50) << "      " << t(15) << "     " << d(51) << std::endl;
    out << S1 << "/    " << r(14) << "    \\            /    " << r(15) << "    \\            /    " << r(16) << "    \\" << std::endl;

    // ROW 7 (Leftmost)
    out << c(36) << "       " << v(13) << "       " << c(37) << h(52) << c(38) << "       " << v(14) << "       " << c(39) << h(53) << c(40) << "       " << v(14) << "       " << c(41) << std::endl;
    out << "   \\                /            \\                /            \\                /" << std::endl;
    out << "   " << d(54) << "             " << d(55) << "      " << t(16) << "     " << d(56) << "             " << d(57) << "      " << t(17) << "     " << d(58) << "             " << d(59) << std::endl;
    out << "     \\            /    " << r(12) << "    \\            /    " << r(13) << "    \\            /" << std::endl;

    // ROW 8
    out << S1 << "  " << c(42) << h(60) << c(43) << "       " << v(15) << "       " << c(44) << h(61) << c(45) << "       " << v(16) << "       " << c(46) << h(62) << c(47) << std::endl;
    out << S2 << "\\                /            \\                /" << std::endl;
    out << S2 << d(63) << "             " << d(64) << "      " << t(18) << "     " << d(65) << "             " << d(66) << std::endl;
    out << S2 << "  \\            /    " << r(15) << "    \\            / " << std::endl;

    // ROW 9 (Tip)
    out << S2 << "  " << c(48) << h(67) << c(49) << "       " << v(0) << "       " << c(50) << h(68) << c(51) << std::endl;
    out << S3 << "\\                /" << std::endl;
    out << S3 << d(69) << "             " << d(70) << std::endl;
    out << S3 << "  \\            /" << std::endl;
    out << S3 << "  " << c(52) << h(71) << c(53) << std::endl;
    out << "-----------------------------------------------------------------------------------------" << std::endl;
}

void Board::print() const {
    display(std::cout);
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    board.display(out);
    return out;
}
