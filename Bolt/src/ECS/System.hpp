#pragma once

#include "../Core/Math.hpp"
#include "../Core/Utils.hpp"
#include "EntityManager.hpp"
#include "Transform.hpp"

namespace Bolt {
	namespace systems {
		namespace transform {
			inline void updateEntityPosition(const u32 &id, const vec3 &pos) {
				auto e = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (e != nullptr) {
					e->setPosition(pos);
				}
			}

			inline void updateEntityRotation(const u32 &id, const vec3 &rot) {
				auto e = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (e != nullptr)
					e->setRotation(rot);
			}
		} // namespace transform

		namespace render {
			inline void renderEntities() {}
		} // namespace render

	} // namespace systems
} // namespace Bolt
