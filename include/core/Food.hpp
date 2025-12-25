#pragma once
#include "core/Types.hpp"

class Food {
public:
    Food() = default;

    const Cell& position() const;
    void setPosition(const Cell& c);

private:
    Cell m_pos{10, 10};
};
