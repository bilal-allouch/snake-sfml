#pragma once

struct Cell {
    int x{};
    int y{};

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

enum class GameState {
    Start,
    Playing,
    Paused,
    GameOver
};

