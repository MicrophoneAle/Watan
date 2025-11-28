// ===== StudyBuddyCard.ixx =====
export module StudyBuddyCard;

import EventCard;

export class StudyBuddyCard : public EventCard {
public:
    void apply(Player& player, Game& game) override;
};
