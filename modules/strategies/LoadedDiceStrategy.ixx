export module LoadedDiceStrategy;

import <iostream>;
import IDiceStrategy;
import RandomGenerator;

export class LoadedDiceStrategy : public IDiceStrategy {
public:
    int roll(RandomGenerator& rng) override;
};
