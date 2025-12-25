#pragma once
#include <SFML/Graphics.hpp>
#include "core/Snake.hpp"

class Renderer {
public:
    Renderer(sf::RenderWindow& window);

    void renderGrid();
    void renderSnake(const Snake& snake);

    int cellSize() const { return CELL_SIZE; }
    int gridWidth() const { return GRID_WIDTH; }
    int gridHeight() const { return GRID_HEIGHT; }


private:
    sf::RenderWindow& m_window;

    static constexpr int CELL_SIZE = 20;
    static constexpr int GRID_WIDTH = 45;
    static constexpr int GRID_HEIGHT = 30;
};
