export module LoadedDiceStrategy;

import <iostream>;
import IDiceStrategy;
import RandomGenerator;

using namespace std;

export class LoadedDiceStrategy : public IDiceStrategy {
public:
    int roll(RandomGenerator& rng) override {
        while (true) {
            cout << "Enter loaded dice roll (2–12): ";
            int x;
            if (cin >> x && x >= 2 && x <= 12) return x;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
};
