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
        Command c;
        stringstream ss(line);
        ss >> c.name >> c.arg;
        return c;
    }
};
