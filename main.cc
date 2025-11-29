import <iostream>;
import <string>;
import <sstream>;

import Game;
import CommandParser;
import CommandExecutor;
import CommandLineParser;

using namespace std;

void printHelp() {
    cout << "Students of Watan - Command Line Options\n";
    cout << "========================================\n\n";
    cout << "Usage: watan [options]\n\n";
    cout << "Options:\n";
    cout << "  -seed <number>      Set random number generator seed\n";
    cout << "  -load <filename>    Load saved game from file\n";
    cout << "  -board <filename>   Load custom board layout from file\n";
    cout << "  -help               Show this help message\n\n";
    cout << "Notes:\n";
    cout << "  - Options can be given in any order\n";
    cout << "  - Only one of -load or -board can be specified\n";
    cout << "  - If no -seed is specified, a default seed is used\n\n";
}

int main(int argc, char* argv[]) {
    // Parse command-line arguments
    CommandLineParser cmdParser;
    CommandLineOptions options = cmdParser.parse(argc, argv);

    // Check for help request
    if (options.helpRequested) {
        printHelp();
        return 0;
    }

    // Check for parsing errors
    if (!options.valid) {
        cerr << options.errorMessage << "\n";
        cerr << "Use -help for usage information.\n";
        return 1;
    }

    // Create game
    Game game;
    CommandParser parser;
    CommandExecutor exec;

    cout << "Watan starting...\n";

    // Apply seed if provided
    if (options.seed.has_value()) {
        cout << "Random seed set to: " << options.seed.value() << "\n";
        game.setSeed(static_cast<unsigned int>(options.seed.value()));
    }

    // Load game or board if specified
    if (options.loadFile.has_value()) {
        cout << "Loading game from: " << options.loadFile.value() << "\n";

        if (!game.loadGame(options.loadFile.value())) {
            cerr << "Failed to load game from file.\n";
            return 1;
        }
        // Game is loaded, skip normal start
    }
    else if (options.boardFile.has_value()) {
        cout << "Loading board from: " << options.boardFile.value() << "\n";

        if (!game.loadBoard(options.boardFile.value())) {
            cerr << "Failed to load board from file.\n";
            return 1;
        }
        // Board is loaded, start normal game
        game.startGame();
    }
    else {
        // Normal game start
        game.startGame();
    }

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
        Command cmd = parser.parse(line);
        exec.execute(cmd, game);
    }
    cout << "\nThanks for playing Students of Watan!\n";
    return 0;
}
