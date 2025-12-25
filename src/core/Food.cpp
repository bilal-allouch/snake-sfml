#include "core/Food.hpp"

const Cell& Food::position() const {
    return m_pos;
}

void Food::setPosition(const Cell& c) {
    m_pos = c;
}
