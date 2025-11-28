export module Game;

import <iostream>;
using namespace std;

export class Game {
public:
    Game() : quit(false) {}

    bool shouldQuit() const { return quit; }
    void requestQuit() { quit = true; }

    void printMessage(const string& msg) {
        cout << msg << "\n";
    }

private:
    bool quit;
};
