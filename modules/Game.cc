module Game;

import <iostream>;
import <array>;
import Player;
import Board;
import RandomGenerator;
import IDiceStrategy;
import FairDiceStrategy;
import LoadedDiceStrategy;
import WatanTypes;

using namespace std;

Game::Game()
    : quit(false),
    currentTurn(1),
    currentPlayer(0), // Blue starts
    board(),
    players{ Player(PlayerColour::Blue),
             Player(PlayerColour::Red),
             Player(PlayerColour::Orange),
             Player(PlayerColour::Yellow) },
    rng(123),
    dice(make_unique<FairDiceStrategy>())
{
    startTurnMessage();
}

bool Game::isRunning() const {
    return !quit;
}

void Game::requestQuit() {
    quit = true;
}

Board& Game::getBoard() {
    return board;
}

Player& Game::getPlayer() {
    return players[currentPlayer];
}

const Player& Game::getPlayer() const {
    return players[currentPlayer];
}

Player& Game::getPlayer(int index) {
    return players.at(index);
}

const Player& Game::getPlayer(int index) const {
    return players.at(index);
}

int Game::getCurrentPlayerIndex() const {
    return currentPlayer;
}

PlayerColour Game::getCurrentPlayerColour() const {
    return players[currentPlayer].getColour();
}

void Game::startTurnMessage() {
    cout << "----------------------------------------\n";
    cout << "Student " << toString(getCurrentPlayerColour()) << "'s turn.\n";
    getPlayer().printStatus(cout);
}

void Game::nextTurn() {
    currentPlayer = (currentPlayer + 1) % 4;
    ++currentTurn;
    startTurnMessage();
}

int Game::rollDice() {
    int val = dice->roll(rng);
    cout << "Student " << toString(getCurrentPlayerColour())
        << " rolled " << val << ".\n";

    board.distributeResources(val);
    return val;
}

void Game::setDiceFair() {
    dice = make_unique<FairDiceStrategy>();
    cout << "Dice set to FAIR for student "
        << toString(getCurrentPlayerColour()) << ".\n";
}

void Game::setDiceLoaded() {
    dice = make_unique<LoadedDiceStrategy>();
    cout << "Dice set to LOADED for student "
        << toString(getCurrentPlayerColour()) << ".\n";
}
