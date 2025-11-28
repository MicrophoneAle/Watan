export module Goal;
import WatanTypes;

export class Goal {
public:
    Goal();
    Goal(int id);

    int getId() const;
    PlayerColour getOwner() const;
    void setOwner(PlayerColour p);

private:
    int id;
    PlayerColour owner;
};