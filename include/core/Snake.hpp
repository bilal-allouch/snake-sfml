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

    void move(); // avance d’une case dans la direction

private:
    std::vector<Cell> m_body;
    Direction m_dir{Direction::Right};
};
