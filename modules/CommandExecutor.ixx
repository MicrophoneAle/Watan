export module CommandExecutor;
import <iostream>;
import <string>;
import CommandParser;
import Game;
import WatanTypes;

export class CommandExecutor {
public:
    void execute(const Command& cmd, Game& game);

private:
    PlayerColour parseColour(const std::string& str) const;
    ResourceType parseResource(const std::string& str) const;
    void executeTrade(Game& game, PlayerColour target, ResourceType give, ResourceType take);
};