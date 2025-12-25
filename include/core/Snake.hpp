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

    Cell nextHead() const;       // calcule la prochaine tête
    void move();                 // avance d’une case
    bool isSelfColliding() const; // tête touche le corps ?

    void reset(); // restart

private:
    std::vector<Cell> m_body;
    Direction m_dir{Direction::Right};
};
