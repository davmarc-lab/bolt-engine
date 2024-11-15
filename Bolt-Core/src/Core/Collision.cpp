#include "../../include/Core/Collision.hpp"
#include <algorithm>
#include <utility>

namespace bolt {
	CollisionPoints CollisionDetection::testCollision(const Collider *a, const Transform *at, const Collider *b, const Transform *bt) {
		b8 swap = b->type > a->type;

		if (swap) {
            std::swap(a, b);
            std::swap(at, bt);
		}

        CollisionPoints points = test[a->type][b->type](a, at, b, bt);

        if (swap) {
            std::swap(points.a, points.b);
            points.normal = -points.normal;
        }

        return points;
	}
} // namespace bolt
