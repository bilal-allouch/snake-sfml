#include "core/Snake.hpp"

Snake::Snake() {
    reset();
}

void Snake::reset() {
    m_body = {
        {22, 15}, {21, 15}, {20, 15}, {19, 15}, {18, 15}
    };
    m_dir = Direction::Right;
    m_grow = 0;
}

const std::vector<Cell>& Snake::body() const {
    return m_body;
}

const Cell& Snake::head() const {
    return m_body.front();
}

void Snake::setDirection(Direction dir) {
    const bool isOpposite =
        (m_dir == Direction::Up    && dir == Direction::Down) ||
        (m_dir == Direction::Down  && dir == Direction::Up)   ||
        (m_dir == Direction::Left  && dir == Direction::Right)||
        (m_dir == Direction::Right && dir == Direction::Left);

    if (!isOpposite) m_dir = dir;
}

Direction Snake::direction() const {
    return m_dir;
}

Cell Snake::nextHead() const {
    Cell next = head();
    switch (m_dir) {
        case Direction::Up:    next.y -= 1; break;
        case Direction::Down:  next.y += 1; break;
        case Direction::Left:  next.x -= 1; break;
        case Direction::Right: next.x += 1; break;
    }
    return next;
}

void Snake::move() {
    const Cell next = nextHead();
    m_body.insert(m_body.begin(), next);

    if (m_grow > 0) {
        m_grow--;
    } else {
        m_body.pop_back();
    }
}

bool Snake::isSelfColliding() const {
    const Cell& h = head();
    for (size_t i = 1; i < m_body.size(); ++i) {
        if (m_body[i] == h) return true;
    }
    return false;
}

void Snake::grow(int amount) {
    if (amount > 0) m_grow += amount;
}

bool Snake::contains(const Cell& c) const {
    for (const auto& part : m_body) {
        if (part == c) return true;
    }
    return false;
}
