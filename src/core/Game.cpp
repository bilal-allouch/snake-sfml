#include "core/Game.hpp"
#include <string>
#include <algorithm>

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

Game::Game(sf::RenderWindow& window)
    : m_window(window),
      m_renderer(window),
      m_rng(std::random_device{}()) {

    // Load font
    if (!m_font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        // If font missing, close immediately (simple behavior)
        m_window.close();
        return;
    }

    // Overlay
    m_overlay.setSize({(float)m_window.getSize().x, (float)m_window.getSize().y});
    m_overlay.setFillColor(sf::Color(0, 0, 0, 150));

    // HUD
    m_hudText.setFont(m_font);
    m_hudText.setCharacterSize(22);
    m_hudText.setFillColor(sf::Color(220, 220, 220));
    m_hudText.setPosition(12.f, 8.f);

    const float W = (float)m_window.getSize().x;
    const float H = (float)m_window.getSize().y;

    m_startText = makeCenteredText(m_font,
        "SNAKE\n\nPress SPACE to start\nPress ESC to quit", 42, W / 2.f, H / 2.f);

    m_pausedText = makeCenteredText(m_font,
        "PAUSED\n\nPress P to resume", 48, W / 2.f, H / 2.f);

    m_gameOverText = makeCenteredText(m_font,
        "GAME OVER\n\nPress R to restart\nPress SPACE to play again", 44, W / 2.f, H / 2.f);

    resetToStart();
}

void Game::run() {
    // Main loop: event -> update -> render
    while (m_window.isOpen()) {
        processEvents();
        sf::Time dt = m_clock.restart();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            return;
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                m_window.close();
                return;
            }

            if (event.key.code == sf::Keyboard::Space) {
                if (m_state == GameState::Start || m_state == GameState::GameOver) {
                    startNewRun();
                }
            }

            if (event.key.code == sf::Keyboard::R) {
                restart();
            }

            if (event.key.code == sf::Keyboard::P) {
                if (m_state == GameState::Playing) setState(GameState::Paused);
                else if (m_state == GameState::Paused) setState(GameState::Playing);
            }

            if (m_state == GameState::Playing) {
                if (event.key.code == sf::Keyboard::Up)    m_snake.setDirection(Direction::Up);
                if (event.key.code == sf::Keyboard::Down)  m_snake.setDirection(Direction::Down);
                if (event.key.code == sf::Keyboard::Left)  m_snake.setDirection(Direction::Left);
                if (event.key.code == sf::Keyboard::Right) m_snake.setDirection(Direction::Right);
            }
        }
    }
}

void Game::update(sf::Time dt) {
    // tick depends on apples eaten
    int currentTickMs = m_baseTickMs - m_applesEaten * m_msStep;
    currentTickMs = std::clamp(currentTickMs, m_minTickMs, m_baseTickMs);
    const sf::Time tick = sf::milliseconds(currentTickMs);

    m_accumulator += dt;

    while (m_state == GameState::Playing && m_accumulator >= tick) {
        const Cell next = m_snake.nextHead();

        if (isOutside(next)) {
            setState(GameState::GameOver);
            break;
        }

        m_snake.move();

        if (m_snake.isSelfColliding()) {
            setState(GameState::GameOver);
            break;
        }

        if (m_snake.head() == m_food.position()) {
            eatApple();
        }

        m_accumulator -= tick;
    }

    // HUD update
    int level = m_applesEaten + 1;
    m_hudText.setString(
        "Score: " + std::to_string(m_score) +
        "   |   Level: " + std::to_string(level) +
        "   |   Speed: " + std::to_string(1000 / currentTickMs) + " t/s"
    );
}

void Game::render() {
    m_window.clear(sf::Color(20, 20, 24));

    m_renderer.renderGrid();
    m_renderer.renderFood(m_food);
    m_renderer.renderSnake(m_snake);
    m_window.draw(m_hudText);

    if (m_state == GameState::Start) {
        m_window.draw(m_overlay);
        m_window.draw(m_startText);
    } else if (m_state == GameState::Paused) {
        m_window.draw(m_overlay);
        m_window.draw(m_pausedText);
    } else if (m_state == GameState::GameOver) {
        m_window.draw(m_overlay);
        m_window.draw(m_gameOverText);
    }

    m_window.display();
}

void Game::resetToStart() {
    m_snake.reset();
    m_score = 0;
    m_applesEaten = 0;
    m_food.setPosition(randomFreeCell());
    m_accumulator = sf::Time::Zero;
    setState(GameState::Start);
}

void Game::startNewRun() {
    m_snake.reset();
    m_score = 0;
    m_applesEaten = 0;
    m_food.setPosition(randomFreeCell());
    m_accumulator = sf::Time::Zero;
    setState(GameState::Playing);
}

void Game::restart() {
    startNewRun();
}

void Game::setState(GameState s) {
    m_state = s;
}

bool Game::isOutside(const Cell& c) const {
    return c.x < 0 || c.y < 0 || c.x >= m_renderer.gridWidth() || c.y >= m_renderer.gridHeight();
}

Cell Game::randomFreeCell() {
    std::uniform_int_distribution<int> dx(0, m_renderer.gridWidth() - 1);
    std::uniform_int_distribution<int> dy(0, m_renderer.gridHeight() - 1);

    Cell c;
    do {
        c = {dx(m_rng), dy(m_rng)};
    } while (m_snake.contains(c));
    return c;
}

void Game::eatApple() {
    m_snake.grow(1);
    m_applesEaten++;
    m_score += 10;
    m_food.setPosition(randomFreeCell());
}
