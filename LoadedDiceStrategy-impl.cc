module LoadedDiceStrategy;

import <iostream>;

import RandomGenerator;

LoadedDiceStrategy::LoadedDiceStrategy() : d1(1), d2(1) { }

void LoadedDiceStrategy::setLoadedValues(int a, int b) {
    if (a >= 1 && a <= 6) {
        d1 = a;
    }
    if (b >= 1 && b <= 6) {
        d2 = b;
    }
}

int LoadedDiceStrategy::roll(RandomGenerator&) {
    return d1 + d2;
}
