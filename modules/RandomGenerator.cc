module RandomGenerator;

int RandomGenerator::intInRange(int low, int high) {
    uniform_int_distribution<int> dist(low, high);
    return dist(engine);
}
