export module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;

using namespace std;

export class CommandExecutor {
public:
    void execute(const Command& cmd, Game& game);
};
