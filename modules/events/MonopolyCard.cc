export module MonopolyCard;

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

using std::cout;
using std::endl;

void MonopolyCard::apply(Player& /*player*/, Game& /*game*/) {
    // Version 9 stub: later this will take all of a chosen resource from other players.
    cout << "[MonopolyCard] Effect not implemented yet." << endl;
}
