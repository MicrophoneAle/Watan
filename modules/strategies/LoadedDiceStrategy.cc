module LoadedDiceStrategy;

import <iostream>;
import RandomGenerator;

LoadedDiceStrategy::LoadedDiceStrategy()
    : v1(1), v2(1) {
}

void LoadedDiceStrategy::setLoadedValues(int a, int b) {
    if (a >= 1 && a <= 6) v1 = a;
    if (b >= 1 && b <= 6) v2 = b;
}

int LoadedDiceStrategy::roll(RandomGenerator&) {
    return v1 + v2;
}
