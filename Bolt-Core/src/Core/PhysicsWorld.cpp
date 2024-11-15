#include <vector>
#include "../../include/Core/Physics.hpp"

#include "../../include/ECS/EntityManager.hpp"

#include "../../include/Core/Collision.hpp"

namespace bolt {
	inline const auto em = EntityManager::instance();
	inline f32 density = 1.f;

	void PhysicsWorld::addEntity(const u32 &id) {
		auto physic = em->getEntityComponent<PhysicComponent>(id);
		auto model = em->getEntityComponent<Transform>(id);
		physic->mass = model->getScale().x * model->getScale().y * density;
		this->m_entities.insert(id);
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

		this->resolveCollisions();

		this->step();
	}

	void PhysicsWorld::resolveCollisions() {
        std::vector<Collision> collisions{};
        auto ids = em->getEntitiesFromComponent<Collider>();

        for (auto a: ids) {
            for (auto b: ids) {
                if (a == b) break;
                
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
                    std::cout << "coll\n";
                }
            }
        }
	}

	void PhysicsWorld::step() {
		for (auto id : this->m_entities) {
			auto model = em->getEntityComponent<Transform>(id);
			auto physic = em->getEntityComponent<PhysicComponent>(id);

			// solver
			physic->force += physic->mass * this->m_gravity;
			physic->velocity += physic->force / physic->mass * this->m_frameTime;
			model->addPosition(physic->velocity * this->m_frameTime);
			physic->force = vec3(0);
		}
	}
} // namespace bolt
