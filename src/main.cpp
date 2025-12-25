#include <SFML/Graphics.hpp>
#include "core/Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Snake - SFML");
    window.setFramerateLimit(60);

    Game game(window);
    game.run();

    return 0;
}
