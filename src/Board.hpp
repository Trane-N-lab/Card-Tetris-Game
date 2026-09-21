#pragma once
#include <string>
#include <vector>

class Board {
public:
    Board(int width, int height);
    int width() const noexcept { return width_; }
    int height() const noexcept { return height_; }
    const std::string& at(int row, int column) const;
    std::string& at(int row, int column);
    bool inBounds(int row, int column) const noexcept;
    bool isEmpty(int row, int column) const;
    void clearCell(int row, int column);
    void clearAll();
    int resolveMatches();

private:
    int width_;
    int height_;
    std::vector<std::vector<std::string>> cells_;
    int markHorizontalMatches(std::vector<std::vector<bool>>& marked) const;
    int markVerticalMatches(std::vector<std::vector<bool>>& marked) const;
    int clearMarked(const std::vector<std::vector<bool>>& marked);
    void applyGravity();
};
