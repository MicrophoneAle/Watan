// ===== GoalSpeedrunCard.ixx =====
export module GoalSpeedrunCard;

import EventCard;

export class GoalSpeedrunCard : public EventCard {
public:
    void apply(Player& player, Game& game) override;
};
