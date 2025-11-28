export module Goal;

import <array>;
import WatanTypes;

export class Goal {
public:
    // id: 0..71 for edges. c1, c2 are adjacent criteria indices (or -1 for now).
    Goal(int id = -1, int c1 = -1, int c2 = -1);

    int getId() const;
    PlayerColour getOwner() const;
    const std::array<int, 2>& getAdjacentCriteria() const;

    bool isOwned() const;

    // Mark as achieved by colour if not already owned.
    void achieve(PlayerColour colour);

    // Allow Board to set adjacency after construction.
    void setAdjacentCriteria(int c1, int c2);

private:
    int id;
    PlayerColour owner;
    bool owned;
    std::array<int, 2> adjacentCriteria;
};