#pragma once
#include <vector>
#include "core/Types.hpp"

class Snake {
public:
    Snake();

    const std::vector<Cell>& body() const;
    const Cell& head() const;

    void setDirection(Direction dir);
    Direction direction() const;

    Cell nextHead() const;
    void move();
    bool isSelfColliding() const;

    void grow(int amount = 1);  // +1 segment
    bool contains(const Cell& c) const;

    void reset();

private:
    std::vector<Cell> m_body;
    Direction m_dir{Direction::Right};
    int m_grow{0};
};
