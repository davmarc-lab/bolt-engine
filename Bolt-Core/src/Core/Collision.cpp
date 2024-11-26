#include "../../include/Core/Collision.hpp"
#include <algorithm>
#include <utility>

namespace bolt {
	f32 major(const vec3 &a) {
		f32 res = a.x;
		if (a.y > res)
			res = a.y;
		if (a.z > res)
			res = a.z;
		return res;
	}

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

	CollisionPoints CollisionDetection::testCirclePlane(const Collider *a, const Transform *at, const Collider *b, const Transform *bt) {
		assert(a->type == ColliderType::collider_plane && b->type == ColliderType::collider_circle);
		auto *A = (PlaneCollider *)a;
		auto *B = (CircleCollider *)b;

		auto ac = B->center + bt->getPosition();
		auto ar = B->radius * major(bt->getScale());

		// TODO: study geometry better
		auto normal = normalize(A->normal) * quat(1, 0, 0, 0);
		auto onPlane = normal * A->distance + at->getPosition();

		auto distance = dot(ac - onPlane, normal);

		if (distance > ar || distance < -ar) {
			return {};
		}

		auto ad = ac - normal * ar;
		auto bd = ac - normal * distance;

		std::cout << "coll\n";
		return {ad, bd, normal, distance, true};
	}

	CollisionPoints CollisionDetection::testCircleCircle(const Collider *a, const Transform *at, const Collider *b, const Transform *bt) {
		assert(a->type == ColliderType::collider_circle && b->type == ColliderType::collider_circle);

		auto *A = (CircleCollider *)a;
		auto *B = (CircleCollider *)b;

		auto ac = A->center + at->getPosition();
		auto bc = B->center + bt->getPosition();

		auto ab = bc - ac;

		auto ar = A->radius * major(at->getScale());
		auto br = B->radius * major(bt->getScale());

		f32 distance = glm::length(ab);

		if (distance < 0.00001f || distance > ar + br) { return {}; }

		auto norm = normalize(ab);
		auto ad = ac + norm * ar;
		auto bd = bc - norm * br;

		return {ad, bd, norm, distance, true};
	}

} // namespace bolt
