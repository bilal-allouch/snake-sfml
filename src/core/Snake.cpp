#include "core/Snake.hpp"

Snake::Snake() {
    m_body = {
        {22, 15}, {21, 15}, {20, 15}, {19, 15}, {18, 15}
    };
    m_dir = Direction::Right;
}

const std::vector<Cell>& Snake::body() const {
    return m_body;
}

const Cell& Snake::head() const {
    return m_body.front();
}

void Snake::setDirection(Direction dir) {
    // Empêche de faire demi-tour instantané (option pro)
    const bool isOpposite =
        (m_dir == Direction::Up    && dir == Direction::Down) ||
        (m_dir == Direction::Down  && dir == Direction::Up)   ||
        (m_dir == Direction::Left  && dir == Direction::Right)||
        (m_dir == Direction::Right && dir == Direction::Left);

    if (!isOpposite) {
        m_dir = dir;
    }
}

Direction Snake::direction() const {
    return m_dir;
}

void Snake::move() {
    Cell next = head();

    switch (m_dir) {
        case Direction::Up:    next.y -= 1; break;
        case Direction::Down:  next.y += 1; break;
        case Direction::Left:  next.x -= 1; break;
        case Direction::Right: next.x += 1; break;
    }

    // Insère nouvelle tête
    m_body.insert(m_body.begin(), next);

    // Retire la dernière case (pas de grow pour l’instant)
    m_body.pop_back();
}
