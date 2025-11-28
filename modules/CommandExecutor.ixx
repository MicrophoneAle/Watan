export module CommandExecutor;

import <iostream>;
import <string>;

import Game;
import CommandParser;

using namespace std;

export class CommandExecutor {
public:
    void execute(const Command& cmd, Game& game) {
        if (cmd.name == "quit") {
            game.requestQuit();
        }
        else if (cmd.name == "say") {
            game.printMessage(cmd.arg);
        }
        else if (cmd.name == "help") {
            printHelp();
        }
        else {
            cout << "Unknown command. Type 'help'.\n";
        }
    }

private:
    void printHelp() {
        cout << "Commands:\n";
        cout << "  help  - show commands\n";
        cout << "  say X - print message\n";
        cout << "  quit  - exit game\n";
    }
};
