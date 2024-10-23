#include "Collision.hpp"

b8 Collision2D::isColliding() {
	return this->m_first.max.x >= this->m_second.min.x &&
		this->m_first.max.y >= this->m_second.min.y &&
		this->m_first.min.x <= this->m_second.max.x &&
		this->m_first.min.y <= this->m_second.max.y;
}
