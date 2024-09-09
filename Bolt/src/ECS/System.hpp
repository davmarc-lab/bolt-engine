#pragma once

#include "../Core/Math.hpp"
#include "../Core/Utils.hpp"
#include "EntityManager.hpp"

#include "../Platform/GlRenderer.hpp"

#include "../../dependencies/glad/include/glad/glad.h"

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

            inline void drawElement(const u32& id) {
                auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
                GlRenderer::drawArrays(mesh->vao, GL_TRIANGLES, 0, 36);
                mesh->vao.unbind();
            }

			inline void drawMainScene() {
				for (auto e : EntityManager::instance()->getEntitiesFromComponent<Mesh>()) {
                    drawElement(e);
				}
			}
		} // namespace render

	} // namespace systems
} // namespace Bolt
