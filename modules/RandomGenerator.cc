export module RandomGenerator;

import <random>;
using namespace std;

export class RandomGenerator {
public:
    // Generates and random seed
    RandomGenerator() : engine(random_device{}()) {}

    // Generates based on a specific seed for the command -seed
    RandomGenerator(unsigned int seed) : engine(seed) {}

    // Generates a random number in the range [low, high]
    int intInRange(int low, int high) {
        uniform_int_distribution<int> dist(low, high);
        return dist(engine);
    }

private:
    default_random_engine engine;
};
