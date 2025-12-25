#include "core/Snake.hpp"

Snake::Snake() {
    // Serpent statique au centre (tête en premier)
    m_body = {
        {22, 15}, {21, 15}, {20, 15}, {19, 15}, {18, 15}
    };
}

const std::vector<Cell>& Snake::body() const {
    return m_body;
}

const Cell& Snake::head() const {
    return m_body.front();
}
