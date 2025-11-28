module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;
import Player;
import LoadedDiceStrategy;

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
            << "  turn\n"
            << "  end\n"
            << "  quit\n"
            << "  complete <criterion>\n"
            << "  improve <criterion>\n"
            << "  achieve <goal>\n";
    }

    else if (cmd.name == "turn") {
        game.startTurnMessage();
    }

    else if (cmd.name == "end") {
        cout << "Ending turn...\n";
        game.nextTurn();
    }

    else if (cmd.name == "board") {
        game.getBoard().display(cout);
    }

    else if (cmd.name == "status") {
        game.getPlayer().printStatus(cout);
    }

    else if (cmd.name == "fair") {
        game.setDiceFair();
    }

    else if (cmd.name == "load") {
        int a, b;
        cout << "Enter two loaded dice values (1–6): ";
        cin >> a >> b;

        auto* ld = new LoadedDiceStrategy();
        ld->setLoadedValues(a, b);

        game.setDiceLoaded();  // swap strategy
        game.rollDice();       // immediate roll (optional)
    }

    else if (cmd.name == "roll") {
        game.rollDice();
    }

    else if (cmd.name == "complete") {
        int x;
        cin >> x;
        game.getPlayer().addCriterion(x);
        cout << "Completed criterion " << x << ".\n";
    }

    else if (cmd.name == "improve") {
        int x;
        cin >> x;
        game.getPlayer().improveCriterion(x);
        cout << "Improved criterion " << x << ".\n";
    }

    else if (cmd.name == "achieve") {
        int x;
        cin >> x;
        game.getPlayer().addGoal(x);
        cout << "Achieved goal " << x << ".\n";
    }

    else if (cmd.name == "quit") {
        game.requestQuit();
    }

    else {
        cout << "Invalid command.\n";
    }
}
