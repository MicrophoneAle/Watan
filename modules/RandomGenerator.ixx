export module RandomGenerator;

import <random>;

using namespace std;

export class RandomGenerator {
public:
    RandomGenerator() : engine(random_device{}()) {}
    RandomGenerator(unsigned int seed) : engine(seed) {}

    int intInRange(int low, int high);

private:
    default_random_engine engine;
};
