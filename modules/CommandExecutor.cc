module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;

using namespace std;

void CommandExecutor::execute(const Command& cmd, Game& game) {

    if (cmd.name == "help") {
        cout << "Commands:\n"
            << "  help\n"
            << "  board\n"
            << "  status\n"
            << "  roll\n"
            << "  fair\n"
            << "  load\n"
            << "  quit\n";
    }
    else if (cmd.name == "board") {
        game.getBoard().display(cout);
    }
    else if (cmd.name == "status") {
        game.getPlayer().printStatus();
    }
    else if (cmd.name == "roll") {
        game.rollDice();
    }
    else if (cmd.name == "fair") {
        game.setDiceFair();
    }
    else if (cmd.name == "load") {
        game.setDiceLoaded();
    }
    else if (cmd.name == "quit") {
        game.requestQuit();
    }
    else {
        cout << "Invalid command.\n";
    }
}
