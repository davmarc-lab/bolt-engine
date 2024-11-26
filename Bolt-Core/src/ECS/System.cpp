#include "../../include/ECS/System.hpp"

namespace bolt {
	inline mat4 base = mat4(1);

	namespace systems {
		namespace transform {
			void updateEntityPosition(u32 id, const vec3 &pos) {
				auto e = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (e != nullptr) {
					e->addPosition(pos);
				}
			}

			void updateEntityRotation(u32 id, const vec3 &rot) {
				auto e = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (e != nullptr)
					e->setRotation(rot);
			}

			void updateModelMatrix(u32 id) {
				auto model = EntityManager::instance()->getEntityComponent<Transform>(id);

				if (!model->isModelMatrixEnable())
					return;
				if (!model->isDirty())
					return;

				const auto pos = translate(base, model->getPosition());
				const auto scl = scale(base, model->getScale());
				model->setQuaternion(quat(model->getRotation()));
				const auto rot = toMat4(model->getQuaternion());

				model->setModelMatrix(pos * scl * rot);
			}

			void updateAllModelMatrix() {
				auto ids = EntityManager::instance()->getEntitiesFromComponent<Transform>();
				for (const auto id : ids) {
					updateModelMatrix(id);
				}
			}
		} // namespace transform

		namespace render {
			void drawElement(u32 id) {
				const auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
				const auto vao = mesh->vao;
				const auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
				const auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id)->shader.get();

				shader->use();
				if (Application::getSceneType() == scene::SCENE_3D) {
					shader->setMat4("view", standardCamera.getViewMatrix());
				}
				shader->setMat4("model", model->getModelMatrix());

				RenderApi::instance()->getRenderer()->drawArraysTriangles(vao, mesh->vertices.size());
				vao.unbind();
			}

			void drawElementIndexed(u32 id) {
				const auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
				const auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
				const auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id)->shader.get();

				shader->use();
				if (Application::getSceneType() == scene::SCENE_3D) {
					shader->setMat4("view", standardCamera.getViewMatrix());
				}
				shader->setMat4("model", model->getModelMatrix());

				RenderApi::instance()->getRenderer()->drawElementsTriangles(mesh->vao, mesh->indices.size());
			}

			void drawAllMeshes() {
				const auto meshes = EntityManager::instance()->getEntitiesFromComponent<Mesh>();
				const auto lights = EntityManager::instance()->getEntitiesFromComponent<Light>();
				for (const auto id : meshes) {
					const auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
					const auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
					auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id);
					if (shader == nullptr) {
						// use default shader
						const auto s = RenderApi::instance()->getRenderer()->getDefaultShader();
						const auto mask = s->getMask();
						s->use();
						if (Application::getSceneType() == scene::SCENE_3D && mask & ShaderConfig::shader_view) {
							s->setMat4("view", standardCamera.getViewMatrix());
						}
						s->setMat4("model", model->getModelMatrix());

						// If shader implements lights, send light informations
						if (mask & ShaderConfig::shader_lights) {
							s->setVec3("viewPos", standardCamera.getCameraPosition());
							auto mat = EntityManager::instance()->getEntityComponent<Material>(id);
							if (mat != nullptr) {
								s->setVec3("material.ambient", mat->ambient);
								s->setVec3("material.diffuse", mat->diffuse);
								s->setVec3("material.specular", mat->specular);
								s->setFloat("material.shininess", mat->shininess);
							}
						}
					} else {
						const auto mask = shader->shader->getMask();
						shader->shader->use();
						if (Application::getSceneType() == scene::SCENE_3D) {
							shader->shader->setMat4("view", standardCamera.getViewMatrix());
						}
						shader->shader->setMat4("model", model->getModelMatrix());
					}

					mesh->render.call();
				}
			}
		} // namespace render
	} // namespace systems

} // namespace bolt
