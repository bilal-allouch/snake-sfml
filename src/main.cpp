#include <SFML/Graphics.hpp>
#include "core/Game.hpp"

/**
 * @brief Program entry point.
 *
 * Creates the main SFML window, initializes the Game object,
 * and starts the main game loop.
 *
 * @return Exit code of the application.
 */
int main() {
    /**
     * @brief Main render window.
     *
     * The window size matches the grid dimensions multiplied
     * by the cell size defined in the Renderer.
     */
    sf::RenderWindow window(sf::VideoMode(900, 600), "Snake - SFML");

    // Limit rendering to 60 frames per second
    window.setFramerateLimit(60);

    /**
     * @brief Game instance.
     *
     * The Game object owns the game loop, state machine,
     * and all high-level gameplay logic.
     */
    Game game(window);

    // Start the game loop
    game.run();

    return 0;
}
