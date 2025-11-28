export module CommandParser;

import <string>;
import <vector>;
import <sstream>;

using namespace std;

export struct Command {
    string name;
    vector<string> args;
};

export class CommandParser {
public:
    Command parse(const string& line);
};