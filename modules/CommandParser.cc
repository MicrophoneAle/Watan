module CommandParser;

import <string>;
import <sstream>;

Command CommandParser::parse(const std::string& line) {
    Command cmd;
    std::istringstream iss(line);
    iss >> cmd.name;
    return cmd;
}
