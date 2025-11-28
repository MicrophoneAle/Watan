export module CommandParser;
import <string>;
import <vector>;
import <sstream>;

export struct Command {
    std::string name;
    std::vector<std::string> args;
};

export class CommandParser {
public:
    Command parse(const std::string& line);
};