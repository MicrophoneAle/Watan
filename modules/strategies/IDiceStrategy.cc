export module IDiceStrategy;

import RandomGenerator;

export class IDiceStrategy {
public:
    virtual ~IDiceStrategy() = default;
    virtual int roll(RandomGenerator& rng) = 0;
};
