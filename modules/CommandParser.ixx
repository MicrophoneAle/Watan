export module CommandParser;

import <string>;
import <sstream>;

using namespace std;

export struct Command {
    string name;
    string arg;
};

export class CommandParser {
public:
    Command parse(const string& line) {
        Command cmd;
        stringstream ss(line);
        ss >> cmd.name;
        ss >> cmd.arg;
        return cmd;
    }
};
