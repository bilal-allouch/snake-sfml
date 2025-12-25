#include "graphics/Renderer.hpp"

Renderer::Renderer(sf::RenderWindow& window)
    : m_window(window) {}

void Renderer::renderGrid() {
    sf::RectangleShape cell;
    cell.setSize({CELL_SIZE - 1.f, CELL_SIZE - 1.f});
    cell.setFillColor(sf::Color(40, 40, 48));

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            m_window.draw(cell);
        }
    }
}

void Renderer::renderSnake(const Snake& snake) {
    // Corps
    sf::RectangleShape segment;
    segment.setSize({CELL_SIZE - 2.f, CELL_SIZE - 2.f});
    segment.setFillColor(sf::Color(0, 170, 90));

    // Tête
    sf::RectangleShape headShape;
    headShape.setSize({CELL_SIZE - 2.f, CELL_SIZE - 2.f});
    headShape.setFillColor(sf::Color(80, 240, 140));

    // Dessiner tête
    const auto& head = snake.head();
    headShape.setPosition(head.x * CELL_SIZE + 1.f, head.y * CELL_SIZE + 1.f);
    m_window.draw(headShape);

    // Dessiner corps
    const auto& body = snake.body();
    for (size_t i = 1; i < body.size(); ++i) {
        segment.setPosition(body[i].x * CELL_SIZE + 1.f, body[i].y * CELL_SIZE + 1.f);
        m_window.draw(segment);
    }
}
