module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;
import Player;

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
        // Show status for all 4 students, in order Blue, Red, Orange, Yellow
        for (int i = 0; i < 4; ++i) {
            game.getPlayer(i).printStatus(cout);
        }
    }

    else if (cmd.name == "criteria") {
        // Show criteria only for the current student
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
        // Reprint current turn banner + current player status
        game.startTurnMessage();
    }

    else if (cmd.name == "next" || cmd.name == "end") {
        cout << "Moving to next student...\n";
        game.nextTurn();
    }

    else if (cmd.name == "complete") {
        int x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Player& p = game.getPlayer();
            p.addCriterion(x);
            cout << "Student completed criterion " << x << ".\n";
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid criterion index.\n";
        }
    }

    else if (cmd.name == "improve") {
        int x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Player& p = game.getPlayer();
            p.improveCriterion(x);
            cout << "Student improved criterion " << x << ".\n";
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid criterion index.\n";
        }
    }

    else if (cmd.name == "achieve") {
        int x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Player& p = game.getPlayer();
            p.addGoal(x);
            cout << "Student achieved goal " << x << ".\n";
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid goal index.\n";
        }
    }

    else if (cmd.name == "quit") {
        game.requestQuit();
    }

    else {
        cout << "Invalid command.\n";
    }
}
