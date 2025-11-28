// ===== CommandExecutor.ixx =====
export module CommandExecutor;

import <iostream>;
import CommandParser;
import Game;

export class CommandExecutor {
public:
    void execute(const Command& cmd, Game& game);
};
