module CommandParser;
import <string>;
import <sstream>;

Command CommandParser::parse(const std::string& line) {
    Command cmd;
    std::istringstream iss(line);

    // Get command name
    iss >> cmd.name;

    // Get all arguments
    std::string arg;
    while (iss >> arg) {
        cmd.args.push_back(arg);
    }

    return cmd;
}