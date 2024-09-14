#pragma once

#include "../Core/Math.hpp"
#include "../Core/Utils.hpp"
#include "EntityManager.hpp"

#include "../Core/RenderApi.hpp"
#include "../Platform/Buffer/GlVertexArray.hpp"

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

			inline void drawElement(const u32 &id) {
				auto vao = EntityManager::instance()->getEntityComponent<Mesh>(id)->vao;
				RenderApi::instance()->getRenderer()->drawArraysTriangles(*vao, 36);
				vao->unbind();
			}

			inline void drawMainScene() {
				for (auto e : EntityManager::instance()->getEntitiesFromComponent<Mesh>()) {
					drawElement(e);
				}
			}
		} // namespace render

	} // namespace systems
} // namespace Bolt
