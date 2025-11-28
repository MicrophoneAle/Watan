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
            // EOF detected - save backup and exit
            cout << "\nEOF detected. Exiting...\n";
            break;
        }

        if (line.empty()) continue;

        // Handle geese placement (waiting for tile number)
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

        // Handle geese steal (waiting for colour name)
        if (game.isWaitingForGeeseSteal()) {
            game.handleGeeseSteal(line);
            continue;
        }

        // Handle initial placement (waiting for criterion number)
        if (game.getGamePhase() == GamePhase::InitialPlacement) {
            try {
                int criterionId = stoi(line);
                if (!game.handleInitialCriterionPlacement(criterionId)) {
                    game.promptInitialPlacement();
                }
            }
            catch (...) {
                cout << "Invalid input. Enter a criterion number (0-53).\n";
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
