#pragma once
#include "Board.hpp"
#include <string>

class Console {
public:
    static void setupUtf8();
    static void clear();
    static bool keyAvailable();
    static int readKey();
    static void sleepMs(unsigned milliseconds);
    static void draw(const Board& board, int score, const std::string& message = {});
};
