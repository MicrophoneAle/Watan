import <iostream>;
import Game;
import CommandParser;
import CommandExecutor;

using namespace std;

int main() {
    Game game;
    CommandParser parser;
    CommandExecutor exec;

    cout << "Watan v4 starting...\n";

    string line;
    while (game.isRunning()) {
        cout << "> ";
        if (!getline(cin, line)) break;

        Command cmd = parser.parse(line);
        exec.execute(cmd, game);
    }

    cout << "Goodbye.\n";
}
