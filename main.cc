import <iostream>;
import <string>;

import Game;
import CommandParser;
import CommandExecutor;

using namespace std;

int main() {
    Game game;
    CommandParser parser;
    CommandExecutor exec;

    cout << "Watan Version 3 Loaded.\n";

    string line;
    while (!game.shouldQuit() && getline(cin, line)) {
        Command cmd = parser.parse(line);
        exec.execute(cmd, game);
    }

    cout << "Goodbye!\n";
}
