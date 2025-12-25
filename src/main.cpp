#include <SFML/Graphics.hpp>
#include <random>
#include <string>
#include <algorithm>

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

static sf::Text makeCenteredText(const sf::Font& font, const std::string& str, unsigned size, float x, float y) {
    sf::Text t;
    t.setFont(font);
    t.setString(str);
    t.setCharacterSize(size);
    t.setFillColor(sf::Color(240, 240, 240));
    auto b = t.getLocalBounds();
    t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
    t.setPosition(x, y);
    return t;
}

int main() {
    constexpr float WIN_W = 900.f;
    constexpr float WIN_H = 600.f;

    sf::RenderWindow window(sf::VideoMode((unsigned)WIN_W, (unsigned)WIN_H), "Snake - SFML");
    window.setFramerateLimit(60);

    Renderer renderer(window);
    Snake snake;
    Food food;

    // RNG
    std::random_device rd;
    std::mt19937 rng(rd());

    // Font
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        return 1;
    }

    // HUD (Score + Level)
    sf::Text hudText;
    hudText.setFont(font);
    hudText.setCharacterSize(22);
    hudText.setFillColor(sf::Color(220, 220, 220));
    hudText.setPosition(12.f, 8.f);

    int score = 0;
    int applesEaten = 0;

    // Game state
    GameState state = GameState::Start;

    // Overlays
    sf::RectangleShape overlay({WIN_W, WIN_H});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    sf::Text startText = makeCenteredText(
        font,
        "SNAKE\n\nPress SPACE to start\nPress ESC to quit",
        42, WIN_W / 2.f, WIN_H / 2.f
    );

    sf::Text pausedText = makeCenteredText(
        font,
        "PAUSED\n\nPress P to resume",
        48, WIN_W / 2.f, WIN_H / 2.f
    );

    sf::Text gameOverText = makeCenteredText(
        font,
        "GAME OVER\n\nPress R to restart\nPress SPACE to play again",
        44, WIN_W / 2.f, WIN_H / 2.f
    );

    // Tick (vitesse)
    const int baseTickMs = 140;     // vitesse de départ
    const int minTickMs  = 60;      // vitesse max (plus petit = plus rapide)
    const int msStep     = 8;       // accélération par pomme
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;

    auto resetGame = [&]() {
        snake.reset();
        score = 0;
        applesEaten = 0;
        food.setPosition(randomFreeCell(rng, renderer.gridWidth(), renderer.gridHeight(), snake));
        accumulator = sf::Time::Zero;
        state = GameState::Playing;
    };

    // Initial placement food (pour Start, au cas où)
    food.setPosition(randomFreeCell(rng, renderer.gridWidth(), renderer.gridHeight(), snake));

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                // Quit
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

                // Start / Play again
                if (event.key.code == sf::Keyboard::Space) {
                    if (state == GameState::Start || state == GameState::GameOver) {
                        resetGame();
                    }
                }

                // Restart
                if (event.key.code == sf::Keyboard::R) {
                    resetGame();
                }

                // Pause toggle
                if (event.key.code == sf::Keyboard::P) {
                    if (state == GameState::Playing) state = GameState::Paused;
                    else if (state == GameState::Paused) state = GameState::Playing;
                }

                // Direction uniquement si on joue
                if (state == GameState::Playing) {
                    if (event.key.code == sf::Keyboard::Up)    snake.setDirection(Direction::Up);
                    if (event.key.code == sf::Keyboard::Down)  snake.setDirection(Direction::Down);
                    if (event.key.code == sf::Keyboard::Left)  snake.setDirection(Direction::Left);
                    if (event.key.code == sf::Keyboard::Right) snake.setDirection(Direction::Right);
                }
            }
        }

        // Calcul vitesse dynamique
        // Plus tu manges, plus ça va vite (tick diminue)
        int currentTickMs = baseTickMs - applesEaten * msStep;
        currentTickMs = std::clamp(currentTickMs, minTickMs, baseTickMs);
        const sf::Time tick = sf::milliseconds(currentTickMs);

        // Update (uniquement en Playing)
        accumulator += clock.restart();
        while (state == GameState::Playing && accumulator >= tick) {
            const Cell next = snake.nextHead();

            // murs
            if (isOutside(next, renderer.gridWidth(), renderer.gridHeight())) {
                state = GameState::GameOver;
                break;
            }

            // avancer
            snake.move();

            // self collision
            if (snake.isSelfColliding()) {
                state = GameState::GameOver;
                break;
            }

            // manger
            if (snake.head() == food.position()) {
                snake.grow(1);
                applesEaten++;
                score += 10;
                food.setPosition(randomFreeCell(rng, renderer.gridWidth(), renderer.gridHeight(), snake));
            }

            accumulator -= tick;
        }

        // HUD text (niveau = pommes mangées + 1)
        int level = applesEaten + 1;
        hudText.setString(
            "Score: " + std::to_string(score) +
            "   |   Level: " + std::to_string(level) +
            "   |   Speed: " + std::to_string(1000 / currentTickMs) + " t/s"
        );

        // Render
        window.clear(sf::Color(20, 20, 24));
        renderer.renderGrid();
        renderer.renderFood(food);
        renderer.renderSnake(snake);
        window.draw(hudText);

        // Overlays selon l’état
        if (state == GameState::Start) {
            window.draw(overlay);
            window.draw(startText);
        } else if (state == GameState::Paused) {
            window.draw(overlay);
            window.draw(pausedText);
        } else if (state == GameState::GameOver) {
            window.draw(overlay);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
