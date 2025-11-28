module Game;

import <iostream>;
import <memory>;

import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import WatanTypes;

using namespace std;

Game::Game() : quit(false), rng(123) {
    player = make_unique<Player>(PlayerColour::Blue);
    dice = make_unique<FairDiceStrategy>();
}

void Game::rollDice() {
    int val = dice->roll(rng);
    cout << "Dice rolled: " << val << "\n";
}
