#include "Console.hpp"
#include "Game.hpp"
#include <iostream>

int main() {
    Console::setupUtf8();
    std::cout << "Welcome to Card Tetris!\n"
              << "Use the arrow keys to move.\n"
              << "Press any key to start...";
    Console::readKey();
    Game game;
    game.run();
    return 0;
}
