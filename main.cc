import <iostream>;
import <string>;

import Game;
import CommandParser;
import CommandExecutor;

using namespace std;

int main() {
    Game game;
    CommandParser parser;
    CommandExecutor executor;

    cout << "Welcome to Watan!\n";

    string line;
    while (!game.shouldQuit() && getline(cin, line)) {
        Command cmd = parser.parse(line);
        executor.execute(cmd, game);
    }

    cout << "Goodbye!\n";
    return 0;
}
