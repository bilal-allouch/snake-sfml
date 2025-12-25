#pragma once
#include <SFML/Graphics.hpp>
#include <random>

#include "graphics/Renderer.hpp"
#include "core/Snake.hpp"
#include "core/Food.hpp"
#include "core/Types.hpp"

class Game {
public:
    explicit Game(sf::RenderWindow& window);
    void run();

private:
    // loop
    void processEvents();
    void update(sf::Time dt);
    void render();

    // game actions
    void resetToStart();
    void startNewRun();
    void restart();
    void setState(GameState s);

    // mechanics
    bool isOutside(const Cell& c) const;
    Cell randomFreeCell();
    void eatApple();

private:
    sf::RenderWindow& m_window;
    Renderer m_renderer;

    Snake m_snake;
    Food m_food;

    // RNG
    std::mt19937 m_rng;

    // UI
    sf::Font m_font;
    sf::Text m_hudText;
    sf::Text m_startText;
    sf::Text m_pausedText;
    sf::Text m_gameOverText;
    sf::RectangleShape m_overlay;

    // state
    GameState m_state{GameState::Start};

    int m_score{0};
    int m_applesEaten{0};

    // timing
    sf::Clock m_clock;
    sf::Time m_accumulator{sf::Time::Zero};

    const int m_baseTickMs = 140;
    const int m_minTickMs  = 60;
    const int m_msStep     = 8;
};
