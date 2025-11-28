export module CommandLineParser;

import <string>;
import <optional>;

using namespace std;

export struct CommandLineOptions {
    optional<int> seed;
    optional<string> loadFile;
    optional<string> boardFile;
    bool helpRequested = false;
    bool valid = true;
    string errorMessage;
};

export class CommandLineParser {
public:
    CommandLineOptions parse(int argc, char* argv[]);

private:
    bool isValidSeed(const string& seedStr, int& seed);
    bool isDigit(char ch);  // Added isDigit function
};
