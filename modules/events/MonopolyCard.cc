module MonopolyCard;

import <iostream>;
import <string>;

import Player;
import Game;
import EventCard;
import WatanTypes;

using namespace std;

void MonopolyCard::apply(Player& player, Game& game) {
    cout << "[MonopolyCard] Monopoly card activated!\n";
    cout << "Student " << toString(player.getColour())
        << " may choose a resource to steal from all other players.\n";
    cout << "Choose resource (Caffeine, Lab, Lecture, Study, Tutorial):\n";
    cout << "> ";

    string input;

    if (!(cin >> input)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
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
        cout << "Invalid resource.\n";
        return;
    }

    int totalStolen = 0;
    PlayerColour currentColour = player.getColour();

    // Steal from all other players
    for (int i = 0; i < 4; i++) {
        Player& otherPlayer = game.getPlayer(i);

        if (otherPlayer.getColour() == currentColour) {
            continue;
        }

        int amount = otherPlayer.getResource(resource);

        if (amount > 0) {
            otherPlayer.spendResource(resource, amount);
            player.addResource(resource, amount);
            totalStolen += amount;
            cout << "Stole " << amount << " " << toString(resource)
                << " from " << toString(otherPlayer.getColour()) << ".\n";
        }
    }
    if (totalStolen == 0) {
        cout << "No resources were stolen.\n";
    }
    else {
        cout << "Total " << toString(resource) << " stolen: " << totalStolen << "\n";
    }
}
