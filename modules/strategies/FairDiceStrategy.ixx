export module FairDiceStrategy;

import IDiceStrategy;
import RandomGenerator;

export class FairDiceStrategy : public IDiceStrategy {
public:
    int roll(RandomGenerator& rng) override {
        return rng.intInRange(1, 6) + rng.intInRange(1, 6);
    }
};
