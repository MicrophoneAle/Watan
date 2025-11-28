export module CourseCriteriaCard;

import EventCard;

export class CourseCriteriaCard : public EventCard {
public:
    void apply(Player& player, Game& game) override;
};
