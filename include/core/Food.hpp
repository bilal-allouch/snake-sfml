#pragma once

#include "core/Types.hpp"

/**
 * @brief Represents the food entity consumed by the snake.
 *
 * The Food class stores the position of the food on the grid
 * and allows it to be repositioned when eaten.
 */
class Food {
public:
    /**
     * @brief Constructs a Food object with a default position.
     */
    Food() = default;

    /**
     * @brief Returns the current position of the food.
     * @return A constant reference to the food cell position.
     */
    const Cell& position() const;

    /**
     * @brief Sets the position of the food on the grid.
     * @param c The new cell position.
     */
    void setPosition(const Cell& c);

private:
    /** @brief Grid position of the food. */
    Cell m_pos{10, 10};
};
