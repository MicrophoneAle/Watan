export module CommandExecutor;

import <iostream>;
import Game;
import CommandParser;

using namespace std;

export class CommandExecutor {
public:
    void execute(const Command& cmd, Game& game) {
        if (cmd.name == "quit") game.requestQuit();
        else if (cmd.name == "help") printHelp();
        else if (cmd.name == "roll") game.rollDice();
        else if (cmd.name == "player") game.getPlayer().printStatus();
        else if (cmd.name == "board") game.getBoard().print();
        else cout << "Unknown command.\n";
    }

private:
    void printHelp() {
        cout << "Commands: help, quit, roll, player, board\n";
    }
};
