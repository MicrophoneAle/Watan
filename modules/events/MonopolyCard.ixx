// ===== MonopolyCard.ixx =====
export module MonopolyCard;

import EventCard;

export class MonopolyCard : public EventCard {
public:
    void apply(Player& player, Game& game) override;
};
