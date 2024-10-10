#include "../../include/Core/Physics.hpp"

#include "../../include/ECS/EntityManager.hpp"

namespace bolt {

	void PhysicsWorld::onAttach() {
		auto ids = EntityManager::instance()->getEntitiesFromComponent<PhysicComponent>();
		for (const auto &id : ids) {
			this->m_entities.insert(id);
		}
	}

	void PhysicsWorld::onDetach() {}

	void PhysicsWorld::onUpdate() {
		this->m_currTime = this->m_time.getTime();
		this->m_frameTime = this->m_currTime - this->m_prevTime;
		this->m_prevTime = this->m_currTime;

		this->m_accumulator += this->m_frameTime;

		while (this->m_accumulator >= this->m_time.getTimeStep()) {
			this->step();
			this->m_accumulator -= this->m_time.getTimeStep();
		}

		// interpolate Physic result
	}

	void PhysicsWorld::step() {
        auto em = EntityManager::instance();
		for (auto id : this->m_entities) {
            auto model = em->getEntityComponent<Transform>(id);
            auto physic = em->getEntityComponent<PhysicComponent>(id);

			// solver
            physic->force += physic->mass * this->m_gravity;
            physic->velocity += physic->force / physic->mass * this->m_time.getTimeStep();
            model->addPosition(physic->velocity * this->m_time.getTimeStep());
            physic->force = vec3(0);
		}
	}

} // namespace bolt
