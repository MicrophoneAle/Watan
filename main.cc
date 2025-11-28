import <iostream>;
import <string>;
import <sstream>;

import Game;
import CommandParser;
import CommandExecutor;

using namespace std;

int main() {
    Game game;
    CommandParser parser;
    CommandExecutor exec;

    cout << "Watan starting...\n";

    game.startGame();

    string line;

    while (game.isRunning()) {
        cout << "> ";

        if (!getline(cin, line)) {
            // EOF detected
            cout << "\nEOF detected. Exiting...\n";
            break;
        }

        if (line.empty()) {
            continue;
        }

        // Handle geese placement
        if (game.isWaitingForGeesePlacement()) {
            try {
                int tileNum = stoi(line);
                game.handleGeesePlacement(tileNum);
            }
            catch (...) {
                cout << "Invalid input. Enter a tile number (0-18).\n";
            }
            continue;
        }

        // Handle geese steal
        if (game.isWaitingForGeeseSteal()) {
            game.handleGeeseSteal(line);
            continue;
        }

        // Handle initial placement
        if (game.getGamePhase() == GamePhase::InitialPlacement) {
            try {
                int id = stoi(line);

                // Check if waiting for goal or criterion
                if (game.isWaitingForInitialGoal()) {
                    // Placing a goal
                    if (!game.handleInitialGoalPlacement(id)) {
                        game.promptInitialPlacement();
                    }
                }
                else {
                    // Placing a criterion
                    if (!game.handleInitialCriterionPlacement(id)) {
                        game.promptInitialPlacement();
                    }
                }
            }
            catch (...) {
                cout << "Invalid input. Enter a number.\n";
                game.promptInitialPlacement();
            }
            continue;
        }

        // Normal command processing
        Command cmd = parser.parse(line);
        exec.execute(cmd, game);
    }
    cout << "\nThanks for playing Students of Watan!\n";
    return 0;
}
