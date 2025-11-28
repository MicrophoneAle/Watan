module LoadedDiceStrategy;

import <iostream>;
import IDiceStrategy;
import RandomGenerator;

using namespace std;

int LoadedDiceStrategy::roll(RandomGenerator& rng) {
    while (true) {
        cout << "Enter a number (2-12): ";
        int x;
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        if (x < 2 || x > 12) {
            cout << "Out of range. Try again.\n";
            continue;
        }
        cin.ignore(9999, '\n'); // flush
        return x;
    }
}
