export module EventCard;

import Player;
import Game;

export class EventCard {
public:
    virtual ~EventCard() = default;
    virtual void apply(Player& player, Game& game) = 0;
};
