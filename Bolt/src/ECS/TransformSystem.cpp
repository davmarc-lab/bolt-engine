#include <ECS/TransformSystem.hpp>

#include <Core/Math.hpp>

#include "EntityManager.hpp"

namespace Bolt {
	void TransformSystem::onUpdate() {
		EntityManager::instance();
	}

}
