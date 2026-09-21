#include "Game.hpp"
#include "Console.hpp"
#include <algorithm>
#include <iostream>

Game::Game(unsigned int seed) : rng_(seed) {}
std::string Game::randomShape() {
    std::uniform_int_distribution<std::size_t> distribution(0, shapes_.size() - 1);
    return shapes_[distribution(rng_)];
}
bool Game::isBlocked(int row, int column) const {
    return row >= kHeight - 1 || !board_.isEmpty(row + 1, column);
}
bool Game::handleInput(int& column, int row, unsigned& delay) {
    if (!Console::keyAvailable()) return false;
    int key = Console::readKey();
    if (key == 224) key = Console::readKey();
    if (key == 75 && column > 0 && board_.isEmpty(row, column - 1)) {
        board_.clearCell(row, column); --column;
    } else if (key == 77 && column < kWidth - 1 && board_.isEmpty(row, column + 1)) {
        board_.clearCell(row, column); ++column;
    } else if (key == 80) {
        delay = 80;
    }
    return true;
}
void Game::playPiece(const std::string& shape) {
    int column = kWidth / 2, row = 0;
    unsigned delay = 300;
    while (true) {
        board_.at(row, column) = shape;
        Console::draw(board_, score_, "Left/Right: move   Down: drop faster");
        handleInput(column, row, delay);
        board_.at(row, column) = shape;
        if (isBlocked(row, column)) break;
        board_.clearCell(row, column);
        ++row;
        Console::sleepMs(delay);
        delay = 300;
    }
}
void Game::run() {
    while (true) {
        playPiece(randomShape());
        score_ += board_.resolveMatches();
        if (!board_.isEmpty(0, kWidth / 2)) {
            Console::draw(board_, score_);
            std::cout << "Game Over! Final score: " << score_ << "\n";
            return;
        }
    }
}
