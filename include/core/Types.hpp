#pragma once

struct Cell {
    int x{};
    int y{};

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};
