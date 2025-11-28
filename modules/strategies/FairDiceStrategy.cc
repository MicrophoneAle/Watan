export module FairDiceStrategy;

import IDiceStrategy;
import RandomGenerator;

export class FairDiceStrategy : public IDiceStrategy {
public:
    int roll(RandomGenerator& rng) override {
        return rng.getInt(1, 6) + rng.getInt(1, 6);
    }
};
