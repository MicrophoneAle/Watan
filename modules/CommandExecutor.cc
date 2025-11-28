module CommandExecutor;

import <iostream>;
import <sstream>;
import CommandParser;
import Game;
import Player;
import WatanTypes;

using namespace std;

void CommandExecutor::execute(const Command& cmd, Game& game) {
    if (cmd.name == "help") {
        cout << "Valid commands:\n"
            << "  board\n"
            << "  status\n"
            << "  criteria\n"
            << "  achieve <goal>\n"
            << "  complete <criterion>\n"
            << "  improve <criterion>\n"
            << "  trade <colour> <give> <take>\n"
            << "  next\n"
            << "  save <file>\n"
            << "  help\n";

        if (game.getGamePhase() == GamePhase::Normal) {
            cout << "Dice commands:\n"
                << "  roll\n"
                << "  fair\n"
                << "  load\n";
        }
    }
    else if (cmd.name == "board") {
        game.getBoard().display(cout);
    }
    else if (cmd.name == "status") {
        for (int i = 0; i < 4; ++i) {
            game.getPlayer(i).printStatus(cout);
        }
    }
    else if (cmd.name == "criteria") {
        game.getPlayer().printCriteria(cout);
    }
    else if (cmd.name == "roll") {
        game.rollDice();
    }
    else if (cmd.name == "fair") {
        game.setDiceFair();
    }
    else if (cmd.name == "load") {
        game.setDiceLoaded();
    }
    else if (cmd.name == "next") {
        game.nextTurn();
    }
    else if (cmd.name == "complete") {
        if (cmd.args.empty()) {
            cout << "Usage: complete <criterion>\n";
            return;
        }

        try {
            int id = stoi(cmd.args[0]);
            game.completeCriterion(id);
        }
        catch (...) {
            cout << "Invalid criterion number.\n";
        }
    }
    else if (cmd.name == "improve") {
        if (cmd.args.empty()) {
            cout << "Usage: improve <criterion>\n";
            return;
        }

        try {
            int id = stoi(cmd.args[0]);
            game.improveCriterion(id);
        }
        catch (...) {
            cout << "Invalid criterion number.\n";
        }
    }
    else if (cmd.name == "achieve") {
        if (cmd.args.empty()) {
            cout << "Usage: achieve <goal>\n";
            return;
        }

        try {
            int id = stoi(cmd.args[0]);
            game.achieveGoal(id);
        }
        catch (...) {
            cout << "Invalid goal number.\n";
        }
    }
    else if (cmd.name == "trade") {
        if (cmd.args.size() < 3) {
            cout << "Usage: trade <colour> <give> <take>\n";
            return;
        }

        // Parse colour
        PlayerColour target = parseColour(cmd.args[0]);
        if (target == PlayerColour::None) {
            cout << "Invalid player colour.\n";
            return;
        }

        // Parse resources
        ResourceType give = parseResource(cmd.args[1]);
        ResourceType take = parseResource(cmd.args[2]);

        if (give == ResourceType::Netflix || take == ResourceType::Netflix) {
            cout << "Invalid resource type.\n";
            return;
        }

        executeTrade(game, target, give, take);
    }
    else if (cmd.name == "save") {
        if (cmd.args.empty()) {
            cout << "Usage: save <filename>\n";
            return;
        }

        game.saveGame(cmd.args[0]);
    }
    else if (cmd.name == "load_game") {
        if (cmd.args.empty()) {
            cout << "Usage: load_game <filename>\n";
            return;
        }

        game.loadGame(cmd.args[0]);
    }
    else if (cmd.name == "quit") {
        game.requestQuit();
    }
    else if (cmd.name == "geese") {
        // Handle geese placement during 7 roll
        if (cmd.args.empty()) {
            cout << "Usage: geese <tile>\n";
            return;
        }

        try {
            int tile = stoi(cmd.args[0]);
            game.moveGeese(tile);
        }
        catch (...) {
            cout << "Invalid tile number.\n";
        }
    }
    else if (cmd.name == "steal") {
        // Handle stealing after geese placement
        if (cmd.args.empty()) {
            cout << "Usage: steal <colour>\n";
            return;
        }

        PlayerColour victim = parseColour(cmd.args[0]);
        if (victim == PlayerColour::None) {
            cout << "Invalid player colour.\n";
            return;
        }

        game.stealResource(victim);
    }
    else {
        cout << "Invalid command.\n";
    }
}

PlayerColour CommandExecutor::parseColour(const string& str) const {
    string lower = str;
    for (char& c : lower) c = tolower(c);

    if (lower == "blue") return PlayerColour::Blue;
    if (lower == "red") return PlayerColour::Red;
    if (lower == "orange") return PlayerColour::Orange;
    if (lower == "yellow") return PlayerColour::Yellow;

    return PlayerColour::None;
}

ResourceType CommandExecutor::parseResource(const string& str) const {
    string lower = str;
    for (char& c : lower) c = tolower(c);

    if (lower == "caffeine") return ResourceType::Caffeine;
    if (lower == "lab") return ResourceType::Lab;
    if (lower == "lecture") return ResourceType::Lecture;
    if (lower == "study") return ResourceType::Study;
    if (lower == "tutorial") return ResourceType::Tutorial;

    return ResourceType::Netflix;
}

void CommandExecutor::executeTrade(Game& game, PlayerColour target, ResourceType give, ResourceType take) {
    // Get target player index
    int targetIdx = static_cast<int>(target) - 1;
    if (targetIdx < 0 || targetIdx >= 4) {
        cout << "Invalid player.\n";
        return;
    }

    Player& currentPlayer = game.getPlayer();
    Player& targetPlayer = game.getPlayer(targetIdx);

    // Check if current player has the resource to give
    if (currentPlayer.getResource(give) < 1) {
        cout << "You do not have enough resources.\n";
        return;
    }

    // Check if target player has the resource to give
    if (targetPlayer.getResource(take) < 1) {
        cout << toString(target) << " does not have that resource.\n";
        return;
    }

    // Propose trade
    cout << toString(game.getCurrentPlayerColour()) << " offers "
        << toString(target) << " one " << toString(give)
        << " for one " << toString(take) << ".\n";
    cout << "Does " << toString(target) << " accept this offer?\n";
    cout << "> ";

    string response;
    if (!(cin >> response)) {
        cout << "Invalid response.\n";
        return;
    }

    string lower = response;
    for (char& c : lower) c = tolower(c);

    if (lower == "yes") {
        // Execute trade
        currentPlayer.spendResource(give, 1);
        currentPlayer.addResource(take, 1);

        targetPlayer.spendResource(take, 1);
        targetPlayer.addResource(give, 1);

        cout << "Trade completed.\n";
    }
    else {
        cout << "Trade declined.\n";
    }
}