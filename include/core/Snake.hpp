#pragma once
#include <vector>
#include "core/Types.hpp"

class Snake {
public:
    Snake();

    const std::vector<Cell>& body() const;
    const Cell& head() const;

private:
    std::vector<Cell> m_body;
};
