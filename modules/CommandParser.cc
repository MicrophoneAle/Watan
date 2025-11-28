module CommandParser;

import <string>;
import <sstream>;

using namespace std;

Command CommandParser::parse(const string& line) {
    Command cmd;
    istringstream iss(line);

    // Get command name
    iss >> cmd.name;

    // Get all arguments
    string arg;

    while (iss >> arg) {
        cmd.args.push_back(arg);
    }

    return cmd;
}
