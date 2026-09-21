#pragma once
#include "Board.hpp"
#include <random>
#include <string>
#include <vector>

class Game {
public:
    static constexpr int kWidth = 10;
    static constexpr int kHeight = 10;
    explicit Game(unsigned int seed = std::random_device{}());
    void run();

private:
    Board board_{kWidth, kHeight};
    int score_ = 0;
    std::mt19937 rng_;
    const std::vector<std::string> shapes_{"♥", "♦", "♣", "♠"};
    std::string randomShape();
    void playPiece(const std::string& shape);
    bool handleInput(int& column, int row, unsigned& delay);
    bool isBlocked(int row, int column) const;
};
