export module RandomGenerator;

import <random>;

using namespace std;

export class RandomGenerator {
public:
    RandomGenerator(unsigned int seed = 0);

    void setSeed(unsigned int seed);
    int getInt(int min, int max);

     

private:
    mt19937 rng;
};
