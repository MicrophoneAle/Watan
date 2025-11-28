export module CommandExecutor;

import <iostream>;
import <string>;

import Game;
import CommandParser;

using namespace std;

export class CommandExecutor {
public:
    void execute(const Command& cmd, Game& game) {
        if (cmd.name == "help") {
            printHelp();
        }
        else if (cmd.name == "quit") {
            game.requestQuit();
        }
        else if (cmd.name == "say") {
            game.getCurrentPlayer().printStatus();
        }
        else if (cmd.name == "player") {
            game.getCurrentPlayer().printStatus();
        }
        else if (cmd.name == "board") {
            game.getBoard().print();
        }
        else cout << "Unknown command. Type 'help'.\n";
    }

private:
    void printHelp() {
        cout << "Commands:\n";
        cout << "  help     - show commands\n";
        cout << "  quit     - exit game\n";
        cout << "  say      - (debug) show player status\n";
        cout << "  player   - show current player\n";
        cout << "  board    - show board info\n";
    }
};
