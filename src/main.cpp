#include <SFML/Graphics.hpp>
#include "graphics/Renderer.hpp"
#include "core/Snake.hpp"
#include "core/Types.hpp"

static bool isOutside(const Cell& c, int w, int h) {
    return c.x < 0 || c.y < 0 || c.x >= w || c.y >= h;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Snake - SFML");
    window.setFramerateLimit(60);

    Renderer renderer(window);
    Snake snake;

    // Font + Text (overlay)
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        // Si la police manque, on ferme (ou tu peux gérer autrement)
        return 1;
    }

    sf::RectangleShape overlay({900.f, 600.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 140)); // noir transparent

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color(240, 240, 240));

    // Centrage du texte
    auto bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    gameOverText.setPosition(900.f / 2.f, 600.f / 2.f);

    bool gameOver = false;

    // Tick
    const sf::Time tick = sf::milliseconds(120);
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (!gameOver) {
                    if (event.key.code == sf::Keyboard::Up)    snake.setDirection(Direction::Up);
                    if (event.key.code == sf::Keyboard::Down)  snake.setDirection(Direction::Down);
                    if (event.key.code == sf::Keyboard::Left)  snake.setDirection(Direction::Left);
                    if (event.key.code == sf::Keyboard::Right) snake.setDirection(Direction::Right);
                }

                // Restart
                if (event.key.code == sf::Keyboard::R) {
                    snake.reset();
                    gameOver = false;
                    accumulator = sf::Time::Zero;
                }
            }
        }

        accumulator += clock.restart();

        while (!gameOver && accumulator >= tick) {
            // 1) Calcul prochaine tête
            const Cell next = snake.nextHead();

            // 2) Collision murs ?
            if (isOutside(next, renderer.gridWidth(), renderer.gridHeight())) {
                gameOver = true;
                break;
            }

            // 3) Avance
            snake.move();

            // 4) Collision corps ?
            if (snake.isSelfColliding()) {
                gameOver = true;
                break;
            }

            accumulator -= tick;
        }

        window.clear(sf::Color(20, 20, 24));
        renderer.renderGrid();
        renderer.renderSnake(snake);

        if (gameOver) {
            window.draw(overlay);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
