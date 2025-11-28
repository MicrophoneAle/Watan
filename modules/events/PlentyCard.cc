module PlentyCard;

import <iostream>;
import <string>;

import Player;
import Game;
import EventCard;
import WatanTypes;

using namespace std;

void PlentyCard::apply(Player& player, Game& game) {
    cout << "[PlentyCard] Year of Plenty card activated!\n";
    cout << "Student " << toString(player.getColour())
        << " may choose 2 resources.\n";

    for (int i = 0; i < 2; i++) {
        cout << "Choose resource " << (i + 1) << " (Caffeine, Lab, Lecture, Study, Tutorial):\n";
        cout << "> ";
        string input;

        if (!(cin >> input)) {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            i--;
            continue;
        }

        // Parse resource
        string lower = input;

        for (char& c : lower) {
            c = tolower(c);
        }

        ResourceType resource = ResourceType::Netflix;
        if (lower == "caffeine") resource = ResourceType::Caffeine;
        else if (lower == "lab") resource = ResourceType::Lab;
        else if (lower == "lecture") resource = ResourceType::Lecture;
        else if (lower == "study") resource = ResourceType::Study;
        else if (lower == "tutorial") resource = ResourceType::Tutorial;

        if (resource == ResourceType::Netflix) {
            cout << "Invalid resource. Please choose: Caffeine, Lab, Lecture, Study, or Tutorial.\n";
            i--;
            continue;
        }
        player.addResource(resource, 1);
        cout << "Received 1 " << toString(resource) << ".\n";
    }
}
