#include <SFML/Graphics.hpp>
#include <random>
#include <string>

#include "graphics/Renderer.hpp"
#include "core/Snake.hpp"
#include "core/Food.hpp"
#include "core/Types.hpp"

static bool isOutside(const Cell& c, int w, int h) {
    return c.x < 0 || c.y < 0 || c.x >= w || c.y >= h;
}

static Cell randomFreeCell(std::mt19937& rng, int w, int h, const Snake& snake) {
    std::uniform_int_distribution<int> dx(0, w - 1);
    std::uniform_int_distribution<int> dy(0, h - 1);

    Cell c;
    do {
        c = {dx(rng), dy(rng)};
    } while (snake.contains(c));
    return c;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Snake - SFML");
    window.setFramerateLimit(60);

    Renderer renderer(window);
    Snake snake;
    Food food;

    // RNG
    std::random_device rd;
    std::mt19937 rng(rd());
    food.setPosition(randomFreeCell(rng, renderer.gridWidth(), renderer.gridHeight(), snake));

    // Font + UI text
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        return 1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(220, 220, 220));
    scoreText.setPosition(10.f, 6.f);

    int score = 0;
    scoreText.setString("Score: 0");

    // Game over overlay
    sf::RectangleShape overlay({900.f, 600.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 140));

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color(240, 240, 240));
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

                if (event.key.code == sf::Keyboard::R) {
                    snake.reset();
                    food.setPosition(randomFreeCell(rng, renderer.gridWidth(), renderer.gridHeight(), snake));
                    score = 0;
                    scoreText.setString("Score: 0");
                    gameOver = false;
                    accumulator = sf::Time::Zero;
                }
            }
        }

        accumulator += clock.restart();

        while (!gameOver && accumulator >= tick) {
            // prochaine tête
            const Cell next = snake.nextHead();

            // murs
            if (isOutside(next, renderer.gridWidth(), renderer.gridHeight())) {
                gameOver = true;
                break;
            }

            // avancer
            snake.move();

            // self
            if (snake.isSelfColliding()) {
                gameOver = true;
                break;
            }

            // manger ?
            if (snake.head() == food.position()) {
                snake.grow(1);
                score += 10;
                scoreText.setString("Score: " + std::to_string(score));
                food.setPosition(randomFreeCell(rng, renderer.gridWidth(), renderer.gridHeight(), snake));
            }

            accumulator -= tick;
        }

        window.clear(sf::Color(20, 20, 24));
        renderer.renderGrid();
        renderer.renderFood(food);
        renderer.renderSnake(snake);
        window.draw(scoreText);

        if (gameOver) {
            window.draw(overlay);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
