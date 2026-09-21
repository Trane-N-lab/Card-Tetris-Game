#include "Board.hpp"
#include <algorithm>
#include <stdexcept>

Board::Board(int width, int height)
    : width_(width), height_(height),
      cells_(height, std::vector<std::string>(width, " ")) {
    if (width <= 0 || height <= 0) throw std::invalid_argument("Board dimensions must be positive.");
}

const std::string& Board::at(int row, int column) const {
    if (!inBounds(row, column)) throw std::out_of_range("Board coordinate out of range.");
    return cells_[row][column];
}
std::string& Board::at(int row, int column) {
    if (!inBounds(row, column)) throw std::out_of_range("Board coordinate out of range.");
    return cells_[row][column];
}
bool Board::inBounds(int row, int column) const noexcept {
    return row >= 0 && row < height_ && column >= 0 && column < width_;
}
bool Board::isEmpty(int row, int column) const { return at(row, column) == " "; }
void Board::clearCell(int row, int column) { at(row, column) = " "; }
void Board::clearAll() {
    for (auto& row : cells_) std::fill(row.begin(), row.end(), " ");
}
int Board::markHorizontalMatches(std::vector<std::vector<bool>>& marked) const {
    int count = 0;
    for (int row = 0; row < height_; ++row) {
        int start = 0;
        while (start < width_) {
            const auto& symbol = cells_[row][start];
            int end = start + 1;
            while (end < width_ && symbol != " " && cells_[row][end] == symbol) ++end;
            if (symbol != " " && end - start >= 3) {
                for (int column = start; column < end; ++column) {
                    if (!marked[row][column]) { marked[row][column] = true; ++count; }
                }
            }
            start = end;
        }
    }
    return count;
}
int Board::markVerticalMatches(std::vector<std::vector<bool>>& marked) const {
    int count = 0;
    for (int column = 0; column < width_; ++column) {
        int start = 0;
        while (start < height_) {
            const auto& symbol = cells_[start][column];
            int end = start + 1;
            while (end < height_ && symbol != " " && cells_[end][column] == symbol) ++end;
            if (symbol != " " && end - start >= 3) {
                for (int row = start; row < end; ++row) {
                    if (!marked[row][column]) { marked[row][column] = true; ++count; }
                }
            }
            start = end;
        }
    }
    return count;
}
int Board::clearMarked(const std::vector<std::vector<bool>>& marked) {
    int removed = 0;
    for (int row = 0; row < height_; ++row)
        for (int column = 0; column < width_; ++column)
            if (marked[row][column]) { cells_[row][column] = " "; ++removed; }
    return removed;
}
void Board::applyGravity() {
    for (int column = 0; column < width_; ++column) {
        int writeRow = height_ - 1;
        for (int row = height_ - 1; row >= 0; --row) {
            if (!isEmpty(row, column)) {
                cells_[writeRow][column] = cells_[row][column];
                if (writeRow != row) cells_[row][column] = " ";
                --writeRow;
            }
        }
        while (writeRow >= 0) cells_[writeRow--][column] = " ";
    }
}
int Board::resolveMatches() {
    std::vector<std::vector<bool>> marked(height_, std::vector<bool>(width_, false));
    const int candidates = markHorizontalMatches(marked) + markVerticalMatches(marked);
    if (candidates == 0) return 0;
    const int removed = clearMarked(marked);
    applyGravity();
    return removed;
}
