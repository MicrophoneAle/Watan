// ===== CommandExecutor.cc =====
module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;
import Player;

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
            << "  quit\n"
            << "  complete <criterion>\n"
            << "  improve <criterion>\n"
            << "  achieve <goal>\n";
    }
    else if (cmd.name == "board") {
        game.getBoard().display(cout);
    }
    else if (cmd.name == "status") {
        game.getPlayer().printStatus(cout);
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

    // -------------------------
    // NEW VERSION 9 COMMANDS
    // -------------------------

    else if (cmd.name == "complete") {
        int x;
        cin >> x;
        Player& p = game.getPlayer();
        p.addCriterion(x);
        cout << "Completed criterion " << x << ".\n";
    }
    else if (cmd.name == "improve") {
        int x;
        cin >> x;
        Player& p = game.getPlayer();
        p.improveCriterion(x);
        cout << "Improved criterion " << x << ".\n";
    }
    else if (cmd.name == "achieve") {
        int x;
        cin >> x;
        Player& p = game.getPlayer();
        p.addGoal(x);
        cout << "Achieved goal " << x << ".\n";
    }

    else if (cmd.name == "quit") {
        game.requestQuit();
    }
    else {
        cout << "Invalid command.\n";
    }
}
