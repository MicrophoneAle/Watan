export module Criterion;

import WatanTypes;

export class Criterion {
public:
    Criterion();
    Criterion(int id);

    int getId() const;
    PlayerColour getOwner() const;
    int getLevel() const;

    void setOwner(PlayerColour p);
    void upgrade();

private:
    int id;
    PlayerColour owner;
    int level;
};
