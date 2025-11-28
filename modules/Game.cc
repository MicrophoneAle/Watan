module Game;

import <iostream>;
import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import LoadedDiceStrategy;

using namespace std;

Game::Game()
    : quit(false),
    board(),
    player(PlayerColour::Blue),
    rng(123),
    dice(make_unique<FairDiceStrategy>()) {
}

bool Game::isRunning() const { return !quit; }
void Game::requestQuit() { quit = true; }

Board& Game::getBoard() { return board; }
Player& Game::getPlayer() { return player; }

int Game::rollDice() {
    int val = dice->roll(rng);
    cout << "You rolled: " << val << "\n";
    board.distributeRessources(val);
    return val;
}

void Game::setDiceFair() {
    dice = make_unique<FairDiceStrategy>();
    cout << "Dice set to FAIR.\n";
}

void Game::setDiceLoaded() {
    dice = make_unique<LoadedDiceStrategy>();
    cout << "Dice set to LOADED.\n";
}
