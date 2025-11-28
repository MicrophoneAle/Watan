export module LoadedDiceStrategy;

import IDiceStrategy;
import RandomGenerator;

export class LoadedDiceStrategy : public IDiceStrategy {
public:
    LoadedDiceStrategy();
    void setLoadedValues(int a, int b);

    int roll(RandomGenerator& rng) override;

private:
    int v1, v2;
};
