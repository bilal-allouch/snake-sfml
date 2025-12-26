#pragma once

/**
 * @brief Represents a position on the grid, expressed in cell coordinates.
 *
 * The game world is grid-based (not pixels). A Cell identifies one tile of the board.
 */
struct Cell {
    /** @brief X coordinate (column index) in the grid. */
    int x{};

    /** @brief Y coordinate (row index) in the grid. */
    int y{};

    /**
     * @brief Checks whether two cells represent the same grid position.
     * @param other The cell to compare with.
     * @return True if both x and y coordinates are equal, false otherwise.
     */
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

/**
 * @brief Movement direction of the snake.
 *
 * Used to compute the next head position.
 */
enum class Direction {
    Up,    /**< Move one cell up (y - 1). */
    Down,  /**< Move one cell down (y + 1). */
    Left,  /**< Move one cell left (x - 1). */
    Right  /**< Move one cell right (x + 1). */
};

/**
 * @brief High-level state of the game.
 *
 * The game transitions between states based on user input and game events.
 */
enum class GameState {
    Start,    /**< Start screen shown before the first run. */
    Playing,  /**< Active gameplay. */
    Paused,   /**< Gameplay paused; updates are stopped. */
    GameOver  /**< Game ended due to a collision. */
};
