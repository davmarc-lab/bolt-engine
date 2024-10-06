#pragma once

#include "../Core/Math.hpp"
#include "../Core/Utils.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"
#include "../Core/RenderApi.hpp"

#include "../Core/Scene.hpp"
#include "../Graphic/Camera/Camera.hpp"

#include "../../../Bolt-Graphics/include/glad/glad.h"

#include <iostream>

namespace bolt {
	namespace systems {
		namespace transform {
			inline void updateEntityPosition(u32 id, const vec3& pos) {
				auto e = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (e != nullptr) {
					e->addPosition(pos);
				}
			}

			inline void updateEntityRotation(u32 id, const vec3& rot) {
				auto e = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (e != nullptr)
					e->setRotation(rot);
			}

            inline void updateModelMatrix(u32 id) {
                auto model = EntityManager::instance()->getEntityComponent<Transform>(id);

                if (!model->isModelMatrixEnable())
                    return;
                if (!model->isDirty())
                    return;
                
                auto base = mat4(1.0f);
                auto pos = translate(base, model->getPosition());
                auto scl = scale(base, model->getScale());
                model->setQuaternion(quat(model->getRotation()));
                auto rot = toMat4(model->getQuaternion());
                
                model->setModelMatrix(pos * scl * rot);
            }

            inline void updateAllModelMatrix() {
                auto ids = EntityManager::instance()->getEntitiesFromComponent<Transform>();
                for (const auto id: ids) {
                    updateModelMatrix(id);
                }
            }
		} // namespace transform

		namespace render {
			inline void drawElement(u32 id) {
				auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
				auto vao = mesh->vao;
                auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
                auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id)->shader.get();

				shader->use();
                shader->setMat4("view", standardCamera.getViewMatrix());
                shader->setMat4("model", model->getModelMatrix());

				RenderApi::instance()->getRenderer()->drawArraysTriangles(*vao, 36);
				vao->unbind();
			}

            inline void drawAllMeshes() {
                const auto meshes = EntityManager::instance()->getEntitiesFromComponent<Mesh>();
                for (const auto id: meshes) {
					auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
					auto vao = mesh->vao;
					auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
					auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id)->shader.get();

					shader->use();
					shader->setMat4("view", standardCamera.getViewMatrix());
					shader->setMat4("model", model->getModelMatrix());

					RenderApi::instance()->getRenderer()->drawArraysTriangles(*vao, 36);
					vao->unbind();
                }
            }
		} // namespace render

	} // namespace systems
} // namespace Bolt
