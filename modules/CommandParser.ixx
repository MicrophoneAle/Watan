export module CommandParser;

import <string>;
import <sstream>;

export struct Command {
    std::string name;
};

export class CommandParser {
public:
    Command parse(const std::string& line);
};
