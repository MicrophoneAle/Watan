module Game;

Game::Game() : quit(false) {
    player = make_unique<Player>("Blue");
}

Player& Game::getCurrentPlayer() {
    return *player;
}

Board& Game::getBoard() {
    return board;
}
