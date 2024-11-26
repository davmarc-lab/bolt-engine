#pragma once

#include "Math.hpp"
#include "Utils.hpp"

#include "Layer.hpp"
#include "Timestep.hpp"

#include "Collision.hpp"

#include <set>

namespace bolt {
	class Solver {
	public:
		virtual void solve(const std::vector<Collision> &collisions, const f32 &dt) {}

		Solver() = default;

		virtual ~Solver() {}
	};

	class PositionSolver : public Solver {
	public:
		virtual void solve(const std::vector<Collision> &collisions, const f32 &dt) override;

		PositionSolver() = default;

		virtual ~PositionSolver() override {}

	};

	class PhysicsWorld : public Layer {
	public:
		PhysicsWorld() :
			Layer("Physic World") {
		}
		
		void addEntity(const u32 &entity);

		void addSolver(const Shared<Solver>& solver);

		inline b8 removeEntity(const u32 &entity) { return this->m_entities.erase(entity); }

		inline size_t Count() const { return this->m_entities.size(); }

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onUpdate() override;

		virtual ~PhysicsWorld() override = default;

	private:
		void resolveCollisions();

		void step();

		std::set<u32> m_entities{};
		std::vector<Shared<Solver>> m_solvers{};

		Timestep m_time{};
		f32 m_accumulator = 0.f;
		f32 m_prevTime = 0.f;
		f32 m_currTime = 0.f;
		f32 m_frameTime = 0.f;
		f32 m_fixedTime = 0.f;

		vec3 m_gravity = vec3(0, -9.81f, 0);
	};

} // namespace bolt
