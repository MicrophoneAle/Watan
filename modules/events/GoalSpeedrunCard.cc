module GoalSpeedrunCard;

import <iostream>;
import <vector>;

import Player;
import Game;
import Board;
import EventCard;

using namespace std;

void GoalSpeedrunCard::apply(Player& player, Game& game) {
    cout << "[GoalSpeedrunCard] Goal Speedrun card activated!\n";
    cout << "Student " << toString(player.getColour())
        << " can achieve 2 goals immediately!\n";

    Board& board = game.getBoard();
    PlayerColour colour = player.getColour();

    // Find all valid goal placements
    vector<int> validGoals;

    for (int i = 0; i < 72; i++) {
        if (board.isValidGoalPlacement(i, colour)) {
            validGoals.push_back(i);
        }
    }

    if (validGoals.empty()) {
        cout << "No valid goals available to achieve.\n";
        return;
    }

    // Achieve up to 2 goals
    int goalsAchieved = 0;
    for (int i = 0; i < min(2, static_cast<int>(validGoals.size())); i++) {
        int goalId = validGoals[i];

        // Update board
        board.getGoals()[goalId].setOwner(colour);

        // Update player
        player.addGoal(goalId);

        cout << "Student " << toString(colour)
            << " achieved goal " << goalId << ".\n";
        goalsAchieved++;
    }
    cout << "Total goals achieved: " << goalsAchieved << "\n";
}
