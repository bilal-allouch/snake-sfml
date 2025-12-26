#pragma once

#include <SFML/Graphics.hpp>
#include "core/Snake.hpp"
#include "core/Food.hpp"

/**
 * @brief Handles all graphical rendering of the game.
 *
 * The Renderer class is responsible for drawing the grid,
 * the snake, the food, and any visual elements related to the game.
 * It does not contain any game logic.
 */
class Renderer {
public:
    /**
     * @brief Constructs a Renderer bound to an SFML window.
     * @param window Reference to the render window used for drawing.
     */
    explicit Renderer(sf::RenderWindow& window);

    /**
     * @brief Renders the background grid.
     *
     * The grid defines the playable area and cell layout.
     */
    void renderGrid();

    /**
     * @brief Renders the snake on the grid.
     * @param snake The snake to render.
     */
    void renderSnake(const Snake& snake);

    /**
     * @brief Renders the food on the grid.
     * @param food The food entity to render.
     */
    void renderFood(const Food& food);

    /**
     * @brief Returns the size of a single grid cell in pixels.
     * @return Cell size in pixels.
     */
    int cellSize() const { return CELL_SIZE; }

    /**
     * @brief Returns the grid width in number of cells.
     * @return Grid width.
     */
    int gridWidth() const { return GRID_WIDTH; }

    /**
     * @brief Returns the grid height in number of cells.
     * @return Grid height.
     */
    int gridHeight() const { return GRID_HEIGHT; }

private:
    /** @brief Reference to the SFML render window. */
    sf::RenderWindow& m_window;

    /** @brief Pixel size of a single grid cell. */
    static constexpr int CELL_SIZE = 20;

    /** @brief Number of horizontal cells in the grid. */
    static constexpr int GRID_WIDTH = 45;

    /** @brief Number of vertical cells in the grid. */
    static constexpr int GRID_HEIGHT = 30;
};
