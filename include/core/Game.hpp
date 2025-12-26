#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "graphics/Renderer.hpp"
#include "core/Snake.hpp"
#include "core/Food.hpp"
#include "core/Types.hpp"

/**
 * @brief Main game controller class (game loop, state machine, and high-level gameplay logic).
 *
 * The Game class owns the core entities (Snake, Food) and coordinates:
 * - Input handling (events)
 * - Fixed-tick updates (movement, collisions, scoring)
 * - Rendering (delegated to Renderer)
 * - State transitions (Start / Playing / Paused / GameOver)
 *
 * This class keeps the application logic centralized and maintainable.
 */
class Game {
public:
    /**
     * @brief Constructs a new Game instance bound to an existing SFML window.
     * @param window Reference to the main render window.
     */
    explicit Game(sf::RenderWindow& window);

    /**
     * @brief Runs the main game loop until the window is closed.
     *
     * Typical loop order:
     * 1) processEvents()
     * 2) update(dt)
     * 3) render()
     */
    void run();

private:
    /**
     * @brief Polls and processes SFML events (keyboard, close event, etc.).
     *
     * Responsible for input handling and triggering state transitions
     * (e.g., Start -> Playing, Playing <-> Paused, restart on GameOver).
     */
    void processEvents();

    /**
     * @brief Updates the game simulation.
     *
     * Uses a fixed-tick accumulator to move the snake at a stable rate.
     * Handles collisions, food consumption, score updates, and speed changes.
     *
     * @param dt Elapsed time since the previous frame.
     */
    void update(sf::Time dt);

    /**
     * @brief Renders the current frame.
     *
     * Draws the grid, food, snake, HUD, and overlays (Start/Pause/GameOver)
     * depending on the current game state.
     */
    void render();

    /**
     * @brief Resets the game into the Start state (initial screen).
     *
     * Initializes entities and UI for a fresh start without entering gameplay.
     */
    void resetToStart();

    /**
     * @brief Starts a new gameplay run (sets state to Playing).
     *
     * Resets snake, score, speed progression, and spawns food.
     */
    void startNewRun();

    /**
     * @brief Restarts the game immediately (alias for starting a new run).
     */
    void restart();

    /**
     * @brief Sets the current game state.
     * @param s The new state to apply.
     */
    void setState(GameState s);

    /**
     * @brief Checks whether a cell is outside the playable grid.
     * @param c The cell to test.
     * @return True if the cell is outside the board, false otherwise.
     */
    bool isOutside(const Cell& c) const;

    /**
     * @brief Generates a random grid cell not occupied by the snake.
     * @return A free cell suitable for spawning food.
     */
    Cell randomFreeCell();

    /**
     * @brief Handles apple consumption.
     *
     * Increases score, grows the snake, increments difficulty,
     * and respawns food to a new valid position.
     */
    void eatApple();

private:
    /** @brief Main render window (owned externally). */
    sf::RenderWindow& m_window;

    /** @brief Renderer responsible for all drawing. */
    Renderer m_renderer;

    /** @brief Snake entity (movement, growth, collisions). */
    Snake m_snake;

    /** @brief Food entity (position on grid). */
    Food m_food;

    /** @brief Random engine used to spawn food positions. */
    std::mt19937 m_rng;

    // --- UI elements (SFML) ---
    /** @brief Font used for HUD and overlays. */
    sf::Font m_font;

    /** @brief HUD text displaying score/level/speed. */
    sf::Text m_hudText;

    /** @brief Start screen text. */
    sf::Text m_startText;

    /** @brief Pause screen text. */
    sf::Text m_pausedText;

    /** @brief Game Over screen text. */
    sf::Text m_gameOverText;

    /** @brief Semi-transparent overlay drawn behind UI texts. */
    sf::RectangleShape m_overlay;

    // --- Game state ---
    /** @brief Current state of the game state machine. */
    GameState m_state{GameState::Start};

    /** @brief Current player score. */
    int m_score{0};

    /** @brief Number of apples eaten (used for difficulty progression). */
    int m_applesEaten{0};

    // --- Timing ---
    /** @brief Frame clock used to compute delta time. */
    sf::Clock m_clock;

    /** @brief Accumulator used to simulate a fixed tick rate. */
    sf::Time m_accumulator{sf::Time::Zero};

    /** @brief Base tick duration in milliseconds (starting speed). */
    const int m_baseTickMs = 140;

    /** @brief Minimum tick duration in milliseconds (maximum speed). */
    const int m_minTickMs  = 60;

    /** @brief Tick reduction per apple eaten (speed increase step). */
    const int m_msStep     = 8;
};
