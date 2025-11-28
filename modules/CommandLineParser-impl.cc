module CommandLineParser;

import <string>;
import <optional>;

using namespace std;

CommandLineOptions CommandLineParser::parse(int argc, char* argv[]) {
    CommandLineOptions options;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-seed") {
            if (i + 1 >= argc) {
                options.valid = false;
                options.errorMessage = "Error: -seed requires a numeric argument";
                return options;
            }

            int seed;

            if (!isValidSeed(argv[i + 1], seed)) {
                options.valid = false;
                options.errorMessage = "Error: -seed requires a valid integer argument";
                return options;
            }

            options.seed = seed;
            i++; // Skip next argument (seed value)
        }
        else if (arg == "-load") {
            if (i + 1 >= argc) {
                options.valid = false;
                options.errorMessage = "Error: -load requires a filename argument";
                return options;
            }
            if (options.boardFile.has_value()) {
                options.valid = false;
                options.errorMessage = "Error: Cannot specify both -load and -board";
                return options;
            }

            options.loadFile = argv[i + 1];
            i++; // Skip next argument (file name)
        }
        else if (arg == "-board") {
            if (i + 1 >= argc) {
                options.valid = false;
                options.errorMessage = "Error: -board requires a filename argument";
                return options;
            }

            if (options.loadFile.has_value()) {
                options.valid = false;
                options.errorMessage = "Error: Cannot specify both -load and -board";
                return options;
            }

            options.boardFile = argv[i + 1];
            i++; // Skip next argument (file name)
        }
        else if (arg == "-help" || arg == "--help" || arg == "-h") {
            options.helpRequested = true;
        }
        else {
            options.valid = false;
            options.errorMessage = "Error: Unknown option '" + arg + "'";
            return options;
        }
    }
    return options;
}

bool CommandLineParser::isValidSeed(const string& seedStr, int& seed) {
    if (seedStr.empty()) {
        return false;
    }

    // Check if it starts with optional minus sign followed by digits
    size_t start = 0;

    if (seedStr[0] == '-') {
        start = 1;
        if (seedStr.length() == 1) {
            return false;
        }
    }

    // Check that all characters in the string from the start are digits
    for (size_t i = start; i < seedStr.length(); ++i) {
        if (!isDigit(seedStr[i])) {
            return false;
        }
    }
    try {
        seed = stoi(seedStr); // Convert the string to an integer
        return true;
    }
    catch (...) {
        return false;
    }
}

bool CommandLineParser::isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}
