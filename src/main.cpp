#include <SFML/Graphics.hpp>
#include "graphics/Renderer.hpp"
#include "core/Snake.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Snake - SFML");
    window.setFramerateLimit(60);

    Renderer renderer(window);
    Snake snake;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(20, 20, 24));
        renderer.renderGrid();
        renderer.renderSnake(snake);
        window.display();
    }

    return 0;
}
