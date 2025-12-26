#pragma once

#include <vector>
#include "core/Types.hpp"

/**
 * @brief Represents the snake entity and its gameplay behavior.
 *
 * The Snake class manages the snake body, movement direction,
 * growth mechanism, and self-collision detection.
 */
class Snake {
public:
    /**
     * @brief Constructs a new Snake with an initial body and direction.
     */
    Snake();

    /**
     * @brief Returns the full body of the snake.
     * @return A constant reference to the vector of body cells.
     */
    const std::vector<Cell>& body() const;

    /**
     * @brief Returns the current head of the snake.
     * @return A constant reference to the head cell.
     */
    const Cell& head() const;

    /**
     * @brief Sets the current movement direction of the snake.
     *
     * Opposite directions are ignored to prevent instant self-collision.
     *
     * @param dir The new direction to apply.
     */
    void setDirection(Direction dir);

    /**
     * @brief Returns the current movement direction.
     * @return The snake direction.
     */
    Direction direction() const;

    /**
     * @brief Computes the next head position based on the current direction.
     *
     * This method does not modify the snake body.
     *
     * @return The cell where the head would move next.
     */
    Cell nextHead() const;

    /**
     * @brief Moves the snake one cell forward.
     *
     * A new head is added and the tail is removed unless the snake is growing.
     */
    void move();

    /**
     * @brief Checks if the snake head collides with its own body.
     * @return True if a self-collision is detected, false otherwise.
     */
    bool isSelfColliding() const;

    /**
     * @brief Increases the snake length by a given number of segments.
     *
     * Growth is applied progressively during subsequent moves.
     *
     * @param amount Number of segments to add (default is 1).
     */
    void grow(int amount = 1);

    /**
     * @brief Checks whether a given cell is occupied by the snake.
     * @param c The cell to test.
     * @return True if the cell is part of the snake body.
     */
    bool contains(const Cell& c) const;

    /**
     * @brief Resets the snake to its initial state.
     *
     * The body, direction, and growth counter are restored to defaults.
     */
    void reset();

private:
    /** @brief Cells composing the snake body (head is at index 0). */
    std::vector<Cell> m_body;

    /** @brief Current movement direction. */
    Direction m_dir{Direction::Right};

    /** @brief Number of segments remaining to grow. */
    int m_grow{0};
};
