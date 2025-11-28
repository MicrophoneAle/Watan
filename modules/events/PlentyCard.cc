export module PlentyCard;

import EventCard;

export class PlentyCard : public EventCard {
public:
    void apply(Player& player, Game& game) override;
};
