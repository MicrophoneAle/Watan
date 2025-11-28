module StudyBuddyCard;

import <iostream>;

import Player;
import Game;
import EventCard;

using namespace std;

void StudyBuddyCard::apply(Player& player, Game& game) {
    cout << "[StudyBuddyCard] Study Buddy card activated!\n";

    // Add study buddy to the player
    player.addStudyBuddy();

    // Check if player has largest study group
    int numBuddies = player.getStudyBuddies();

    if (numBuddies >= 3) {
        // Check all players to see who has largest study group
        int maxBuddies = 0;
        int playersWithMax = 0;
        Player* playerWithMax = nullptr;

        for (int i = 0; i < 4; i++) {
            Player& p = game.getPlayer(i);
            int buddies = p.getStudyBuddies();

            if (buddies > maxBuddies) {
                maxBuddies = buddies;
                playersWithMax = 1;
                playerWithMax = &p;
            }
            else if (buddies == maxBuddies) {
                playersWithMax++;
            }
        }

        // Award largest study group if this player has strictly more than anyone else
        if (playerWithMax == &player && playersWithMax == 1 && maxBuddies >= 3) {
            // Remove largest study group from all players first
            for (int i = 0; i < 4; i++) {
                game.getPlayer(i).setLargestStudyGroup(false);
            }
            player.setLargestStudyGroup(true);
            cout << toString(player.getColour()) << " now has the Largest Study Group!\n";
        }
    }

    // Move geese
    cout << "Student " << toString(player.getColour())
        << " must move the GEESE.\n";

    game.handleGeese();
}
