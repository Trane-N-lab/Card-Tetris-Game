#include "Console.hpp"

#include <conio.h>
#include <iostream>
#include <windows.h>

void Console::setupUtf8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Console::clear() {
    system("cls");
}

bool Console::keyAvailable() {
    return _kbhit() != 0;
}

int Console::readKey() {
    return _getch();
}

void Console::sleepMs(unsigned milliseconds) {
    Sleep(milliseconds);
}

void Console::draw(const Board& board, int score, const std::string& message) {
    clear();

    std::cout << "+";

    for (int column = 0; column < board.width(); ++column) {
        std::cout << "---+";
    }

    std::cout << '\n';

    for (int row = 0; row < board.height(); ++row) {
        std::cout << "|";

        for (int column = 0; column < board.width(); ++column) {
            std::cout << ' ' << board.at(row, column) << " |";
        }

        std::cout << '\n';

        std::cout << "+";

        for (int column = 0; column < board.width(); ++column) {
            std::cout << "---+";
        }

        std::cout << '\n';
    }

    std::cout << "Score: " << score << '\n';

    if (!message.empty()) {
        std::cout << message << '\n';
    }
}