#pragma once

#include "Math.hpp"
#include "Utils.hpp"

#include "Layer.hpp"
#include "Timestep.hpp"

#include <set>

namespace bolt {
	class PhysicsWorld : public Layer {
	public:
		PhysicsWorld() :
			Layer("Physic World") {}

		void addEntity(const u32 &entity);

		inline b8 removeEntity(const u32 &entity) { return this->m_entities.erase(entity); }

		inline u16 Count() const { return this->m_entities.size(); }

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onUpdate() override;

		virtual ~PhysicsWorld() {}

	private:
		void resolveCollisions();

		void step();

		std::set<u32> m_entities;

		Timestep m_time{};
		f32 m_accumulator = 0.f;
		f32 m_prevTime = 0.f;
		f32 m_currTime = 0.f;
		f32 m_frameTime = 0.f;
		f32 m_fixedTime = 0.f;

		vec3 m_gravity = vec3(0, -9.81f, 0);
	};

	/* struct CollisionPoints {
		vec3 first{};
		vec3 second{};
		vec3 normal{};
		f32 depth = 0;
		b8 colliding = false;
	};

	struct Collision {
	public:
		u32 first = 0, second = 0;
		CollisionPoints points{};

	b8	CollisionPoints testCircleCircle();
	b8	CollisionPoints testCirclePlane();
	}; */

} // namespace bolt
