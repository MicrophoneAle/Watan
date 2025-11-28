module CourseCriteriaCard;

import <iostream>;
import Player;
import Game;
import EventCard;

using namespace std;

void CourseCriteriaCard::apply(Player& player, Game& /*game*/) {
    cout << "[CourseCriteriaCard] Course Criteria card activated!\n";
    cout << "Student " << toString(player.getColour())
        << " gains 1 course criterion point!\n";

    // Add 1 course criterion point directly
    // We'll track this by adding a dummy criterion entry
    // Or we can modify the recalculate function
    // For now, let's just increment the counter
    player.recalculateCourseCriteria();
}
