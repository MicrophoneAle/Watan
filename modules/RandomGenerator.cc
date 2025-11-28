module RandomGenerator;

import <random>;

using namespace std;

RandomGenerator::RandomGenerator(unsigned int seed) : rng(seed) {
    // If seed is 0, use a default seed for consistent testing
    if (seed == 0) {
        rng.seed(123); // Default seed for reproducibility
    }
}

void RandomGenerator::setSeed(unsigned int seed) {
    if (seed == 0) {
        rng.seed(123); // Default seed
    }
    else {
        rng.seed(seed);
    }
}

int RandomGenerator::getInt(int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}
