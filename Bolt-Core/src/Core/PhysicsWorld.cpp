#include <vector>
#include "../../include/Core/Physics.hpp"

#include "../../include/ECS/EntityManager.hpp"

#include "../../include/Core/Collision.hpp"

namespace bolt {
	inline const auto em = EntityManager::instance();
	inline f32 density = 1.f;

	void PositionSolver::solve(const std::vector<Collision> &collisions, const f32 &dt) {
		for (auto c : collisions) {
			auto at = em->getEntityComponent<Transform>(c.a);
			auto bt = em->getEntityComponent<Transform>(c.b);

			auto ap = em->getEntityComponent<PhysicComponent>(c.a);
			auto bp = em->getEntityComponent<PhysicComponent>(c.b);

			auto am = ap->isStatic ? 0 : ap->mass;
			auto bm = bp->isStatic ? 0 : bp->mass;

			const f32 percent = 0.8f;
			const f32 slop = 0.01f;

			auto correction = c.points.normal * percent * glm::fmax(c.points.depth - slop, 0.f) / (am + bm);

			if (!ap->isStatic) {
				ap->velocity = vec3(0);
				at->setPosition(at->getPosition() - (am * correction));
			}
			if (!bp->isStatic) {
				bp->velocity = vec3(0);
				bt->setPosition(bt->getPosition() + (bm * correction));
			}
		}
	}

	void PhysicsWorld::addEntity(const u32 &id) {
		auto physic = em->getEntityComponent<PhysicComponent>(id);
		auto model = em->getEntityComponent<Transform>(id);
		physic->mass = model->getScale().x * model->getScale().y * density;
		this->m_entities.insert(id);
	}

	void PhysicsWorld::addSolver(const Shared<Solver> &solver) {
		this->m_solvers.push_back(solver);
	}

	void PhysicsWorld::onAttach() {
		auto ids = em->getEntitiesFromComponent<PhysicComponent>();
		for (const auto &id : ids) {
			this->m_entities.insert(id);
		}
		this->m_attached = true;
	}

	void PhysicsWorld::onDetach() {}

	void PhysicsWorld::onUpdate() {
		this->m_currTime = this->m_time.getTime();
		this->m_frameTime = this->m_currTime - this->m_prevTime;
		this->m_prevTime = this->m_currTime;

		this->step();
		this->resolveCollisions();

	}

	void PhysicsWorld::resolveCollisions() {
		std::vector<Collision> collisions{};
		auto ids = em->getEntitiesFromComponent<Collider>();

		// detect collisions
		for (auto a : ids) {
			for (auto b : ids) {

				if (a == b)
					break;

				auto ac = em->getEntityComponent<Collider>(a);
				auto bc = em->getEntityComponent<Collider>(b);

				if (!ac || !bc) {
					std::cout << "skip\n";
					continue;
				}

				auto at = em->getEntityComponent<Transform>(a);
				auto bt = em->getEntityComponent<Transform>(b);

				CollisionPoints points = CollisionDetection::testCollision(ac.get(), at.get(), bc.get(), bt.get());
				if (points.colliding) {
					collisions.emplace_back(a, b, points);
				}
			}
		}

		// solve collisions
		for (auto s : this->m_solvers) {
			s->solve(collisions, this->m_frameTime);
		}
	}

	void PhysicsWorld::step() {
		for (auto id : this->m_entities) {
			auto physic = em->getEntityComponent<PhysicComponent>(id);
			if (physic->isStatic)
				continue;
			auto model = em->getEntityComponent<Transform>(id);

			// solver
			physic->force += physic->mass * this->m_gravity;
			physic->velocity += physic->force / physic->mass * this->m_frameTime;
			model->addPosition(physic->velocity * this->m_frameTime);
			physic->force = vec3(0);
		}
	}
} // namespace bolt
