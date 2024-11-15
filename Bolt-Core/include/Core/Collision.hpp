#pragma once

#include "Math.hpp"

#include "../ECS/Component.hpp"

namespace bolt {
	enum ColliderType {
		collider_circle,
		collider_plane,
		collider_square,
	};

	struct Collider : public Component {
		ColliderType type;

		Collider(const ColliderType &type = ColliderType::collider_square) :
			type(type) {}

		Collider(const Collider &other) :
			type(other.type) {}

		virtual ~Collider() = default;
	};

	struct CircleCollider : public Collider {
		vec3 center{};
		f32 radius = 1.f;

		CircleCollider(const vec3 &center, const f32 &radius) :
			Collider(ColliderType::collider_circle), center(center), radius(radius) {}

		CircleCollider() = delete;

		~CircleCollider() override = default;
	};

	struct PlaneCollider : public Collider {
		vec3 normal{};
		f32 distance = 0;

		PlaneCollider() = delete;

		PlaneCollider(const vec3 &normal, const f32 &distance) :
			Collider(ColliderType::collider_plane), normal(normal), distance(distance) {}

		~PlaneCollider() override = default;
	};

	struct CollisionPoints {
		vec3 a{};
		vec3 b{};
		vec3 normal{};
		f32 depth = 0;
		b8 colliding;
	};

	struct Collision {
		u32 a = 0;
		u32 b = 0;
		CollisionPoints points{};
	};

	class CollisionDetection {
	private:
		static CollisionPoints testCircleCircle(const Collider *a, const Transform *at,
												const Collider *b, const Transform *bt){}

		static CollisionPoints testCirclePlane(const Collider *a, const Transform *at,
											   const Collider *b, const Transform *bt) {}

		using DetectionFunc = CollisionPoints (*)(const Collider *a, const Transform *at,
												  const Collider *b, const Transform *bt);

		inline static const DetectionFunc test[2][2]{
			// Circle           Plane
			{testCircleCircle, testCirclePlane}, // Circle
			{nullptr, nullptr},					 // Plane
		};

	public:
		static CollisionPoints testCollision(const Collider *a, const Transform *at,
											 const Collider *b, const Transform *bt);

		CollisionDetection() = delete;

		CollisionDetection(const CollisionDetection &other) = delete;

		~CollisionDetection() = default;
	};

} // namespace bolt
