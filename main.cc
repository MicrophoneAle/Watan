import <iostream>;
import <string>;
import <sstream>;
import Game;
import CommandParser;
import CommandExecutor;

using namespace std;

int main(int argc, char* argv[]) {
    Game game;
    CommandParser parser;
    CommandExecutor exec;

    cout << "========================================\n";
    cout << "  STUDENTS OF WATAN\n";
    cout << "========================================\n\n";

    // Check for command-line arguments
    bool loadGame = false;
    string loadFile;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-load" && i + 1 < argc) {
            loadGame = true;
            loadFile = argv[i + 1];
            i++;
        }
        else if (arg == "-seed" && i + 1 < argc) {
            // Handle seed (would need to pass to Game constructor)
            i++;
        }
    }

    if (loadGame) {
        if (!game.loadGame(loadFile)) {
            cout << "Failed to load game. Starting new game...\n";
            game.startGame();
        }
    }
    else {
        game.startGame();
    }

    string line;

    while (game.isRunning()) {
        cout << "> ";

        if (!getline(cin, line)) {
            // EOF detected - save backup
            cout << "\nEOF detected. Saving backup...\n";
            game.saveGame("backup.sv");
            break;
        }

        // Skip empty lines
        if (line.empty()) continue;

        // Handle initial placement specially
        if (game.getGamePhase() == GamePhase::InitialPlacement) {
            try {
                int criterionId = stoi(line);
                if (!game.handleInitialCriterionPlacement(criterionId)) {
                    game.promptInitialPlacement();
                }
            }
            catch (...) {
                cout << "Invalid input. Please enter a criterion number.\n";
                game.promptInitialPlacement();
            }
            continue;
        }

        // Handle geese placement (waiting for tile selection)
        if (line.find("geese") == string::npos &&
            game.getBoard().getGeeseTileIndex() == -2) { // Special flag for "waiting for geese"
            try {
                int tileId = stoi(line);
                if (game.moveGeese(tileId)) {
                    // Now waiting for steal target
                }
            }
            catch (...) {
                cout << "Invalid tile number.\n";
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