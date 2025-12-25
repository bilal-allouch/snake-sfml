#include <SFML/Graphics.hpp>
#include "graphics/Renderer.hpp"
#include "core/Snake.hpp"
#include "core/Types.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Snake - SFML");
    window.setFramerateLimit(60);

    Renderer renderer(window);
    Snake snake;

    // Timer (tick)
    const sf::Time tick = sf::milliseconds(120); // vitesse du snake
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Input clavier (flèches)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)    snake.setDirection(Direction::Up);
                if (event.key.code == sf::Keyboard::Down)  snake.setDirection(Direction::Down);
                if (event.key.code == sf::Keyboard::Left)  snake.setDirection(Direction::Left);
                if (event.key.code == sf::Keyboard::Right) snake.setDirection(Direction::Right);
            }
        }

        // Update à tick fixe
        accumulator += clock.restart();
        while (accumulator >= tick) {
            snake.move();
            accumulator -= tick;
        }

        // Render
        window.clear(sf::Color(20, 20, 24));
        renderer.renderGrid();
        renderer.renderSnake(snake);
        window.display();
    }

    return 0;
}
