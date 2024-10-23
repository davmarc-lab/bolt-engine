#include "Collision.hpp"

b8 Collision2D::isColliding() {
    auto cx = this->m_first.min.x <= this->m_second.max.x && this->m_first.max.x >= this->m_second.min.x;
    auto cy = this->m_first.min.y <= this->m_second.max.y && this->m_first.max.y >= this->m_second.min.y;
    std::cout << "DEBUG:\n" << to_string(this->m_first.min) << ", " << to_string(this->m_first.max) << "\n";
    std::cout << to_string(this->m_second.min) << ", " << to_string(this->m_second.max) << "\n";
    return cx && cy;
}
