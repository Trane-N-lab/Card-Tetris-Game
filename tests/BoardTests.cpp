#include "Board.hpp"
#include <cassert>
#include <iostream>

void testHorizontalThreeMatch() {
    Board board(5, 5);
    board.at(4, 0) = "♥"; board.at(4, 1) = "♥"; board.at(4, 2) = "♥";
    assert(board.resolveMatches() == 3);
    assert(board.isEmpty(4, 0) && board.isEmpty(4, 1) && board.isEmpty(4, 2));
}
void testHorizontalFourMatch() {
    Board board(5, 5);
    for (int c = 0; c < 4; ++c) board.at(4, c) = "♠";
    assert(board.resolveMatches() == 4);
}
void testVerticalMatch() {
    Board board(5, 5);
    for (int r = 2; r < 5; ++r) board.at(r, 1) = "♦";
    assert(board.resolveMatches() == 3);
}
void testGravityAfterMatch() {
    Board board(4, 5);
    board.at(1, 0) = "♣"; board.at(3, 0) = "♠";
    board.at(4, 1) = "♦"; board.at(4, 2) = "♦"; board.at(4, 3) = "♦";
    assert(board.resolveMatches() == 3);
    assert(board.at(4, 0) == "♠" && board.at(3, 0) == "♣");
}
void testNoMatch() {
    Board board(3, 3);
    board.at(2, 0) = "♥"; board.at(2, 1) = "♦"; board.at(2, 2) = "♣";
    assert(board.resolveMatches() == 0);
}
int main() {
    testHorizontalThreeMatch(); testHorizontalFourMatch(); testVerticalMatch();
    testGravityAfterMatch(); testNoMatch();
    std::cout << "All Card Tetris unit tests passed.\n";
}
