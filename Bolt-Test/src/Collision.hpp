#pragma once

#include "../../Bolt-Core/include/Engine.hpp"

class Collision {
public:
	Collision() {}

	virtual b8 isColliding() = 0;

	virtual ~Collision() = default;
};

struct CollisionPoints {
	bolt::vec3 min = bolt::vec3(0);
	bolt::vec3 max = bolt::vec3(0);
};

class Collision2D : public Collision {
public:
	virtual b8 isColliding() override;
	
	Collision2D(const CollisionPoints &first, const CollisionPoints &second) :
		m_first(first), m_second(second) {}

	virtual ~Collision2D() override = default;

private:
	CollisionPoints m_first{};
	CollisionPoints m_second{};
};
