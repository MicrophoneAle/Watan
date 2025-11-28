export module Player;

import <iostream>;
import <string>;
using namespace std;

export class Player {
public:
    Player(string name) : name(name) {}

    string getName() const {
        return name; 
    }

    void printStatus() const {
        cout << "[Player] " << name << " ready.\n";
    }

private:
    string name;
};
