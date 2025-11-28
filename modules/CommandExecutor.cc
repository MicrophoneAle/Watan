module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;
import Player;
import WatanTypes;

using namespace std;

void CommandExecutor::execute(const Command& cmd, Game& game) {

    if (cmd.name == "help") {
        cout << "Valid commands:\n"
            << "  help\n"
            << "  board\n"
            << "  status\n"
            << "  criteria\n"
            << "  roll\n"
            << "  fair\n"
            << "  load\n"
            << "  turn\n"
            << "  next\n"
            << "  complete <criterion>\n"
            << "  improve <criterion>\n"
            << "  achieve <goal>\n"
            << "  quit\n";
    }

    else if (cmd.name == "board") {
        game.getBoard().display(cout);
    }

    else if (cmd.name == "status") {
        for (int i = 0; i < 4; ++i) {
            game.getPlayer(i).printStatus(cout);
        }
    }

    else if (cmd.name == "criteria") {
        game.getPlayer().printCriteria(cout);
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

    else if (cmd.name == "turn") {
        game.startTurnMessage();
    }

    else if (cmd.name == "next" || cmd.name == "end") {
        cout << "Moving to next student...\n";
        game.nextTurn();
    }

    else if (cmd.name == "complete") {
        int x;
        if (cin >> x) {
            Player& p = game.getPlayer();
            p.addCriterion(x);
            cout << "Student completed criterion " << x << ".\n";
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid value.\n";
        }
    }

    else if (cmd.name == "improve") {
        int x;
        if (cin >> x) {
            Player& p = game.getPlayer();
            p.improveCriterion(x);
            cout << "Student improved criterion " << x << ".\n";
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid value.\n";
        }
    }

    else if (cmd.name == "achieve") {
        int x;
        if (cin >> x) {
            Player& p = game.getPlayer();
            p.addGoal(x);
            cout << "Student achieved goal " << x << ".\n";
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid value.\n";
        }
    }

    else if (cmd.name == "quit") {
        game.requestQuit();
    }

    else {
        cout << "Invalid command.\n";
    }
}
