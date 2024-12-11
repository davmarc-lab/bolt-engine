#include "../../include/ECS/System.hpp"
#include <memory>

namespace bolt {
	inline mat4 base = mat4(1);

	namespace systems {
		namespace ecs {
			std::array<ShaderLightBlock, ::bolt::ecs::MAX_LIGHTS> retrieveLightsData() {
				auto res = std::array<ShaderLightBlock, ::bolt::ecs::MAX_LIGHTS>();
				size_t index = 0;
				for (auto [id, l] : EntityManager::instance()->getLights()) {
					switch (l->getLight()->type) {
						case LIGHT_DIRECTIONAL: {
							auto cast = std::static_pointer_cast<DirectionalLight>(l->getLight());
							res[index].direction = cast->direction;
							break;
						}
						case LIGHT_POINT: {
							auto cast = std::static_pointer_cast<PointLight>(l->getLight());
							res[index].position = cast->position;
							res[index].constant = cast->info.constant;
							res[index].linear = cast->info.linear;
							res[index].quadratic = cast->info.quadratic;
							break;
						}
						case LIGHT_SPOT: {
							auto cast = std::static_pointer_cast<SpotLight>(l->getLight());
							res[index].position = cast->position;
							res[index].direction = cast->direction;
							res[index].constant = cast->info.constant;
							res[index].linear = cast->info.linear;
							res[index].quadratic = cast->info.quadratic;
							res[index].cutoff = cast->cutoff;
							res[index].outerCutoff = cast->outerCutoff;
							break;
						}
						default: {
							std::cerr << "Invalid Light Type\n";
							break;
						}
					}
					res[index].type = l->getLight()->type;
					res[index].color = l->getLight()->color;
					res[index].intensity = l->getLight()->intensity;
					res[index].ambient = l->getLight()->vectors.ambient;
					res[index].diffuse = l->getLight()->vectors.diffuse;
					res[index].specular = l->getLight()->vectors.specular;

					// increment index
					index++;
				}
				return std::move(res);
			}

			void sendLightData(const ShaderProgram &shader) {
				const auto lights = retrieveLightsData();
				shader.use();
				for (auto index = 0; index < lights.size() && index < EntityManager::instance()->getLightsCount(); index++) {
					auto l = lights[index];
					shader.setVec3("lights[" + std::to_string(index) + "].color", l.color);
					shader.setFloat("lights[" + std::to_string(index) + "].intensity", l.intensity);
					shader.setInt("lights[" + std::to_string(index) + "].type", l.type);
					shader.setBool("lights[" + std::to_string(index) + "].isSmooth", l.isSmooth);
					shader.setVec3("lights[" + std::to_string(index) + "].ambient", l.ambient);
					shader.setVec3("lights[" + std::to_string(index) + "].diffuse", l.diffuse);
					shader.setVec3("lights[" + std::to_string(index) + "].specular", l.specular);

					switch (l.type) {
						case LightType::LIGHT_DIRECTIONAL: {
							shader.setVec3("lights[" + std::to_string(index) + "].direction", l.direction);
							break;
						}
						case LightType::LIGHT_POINT: {
							shader.setVec3("lights[" + std::to_string(index) + "].position", l.position);
							shader.setFloat("lights[" + std::to_string(index) + "].constant", l.constant);
							shader.setFloat("lights[" + std::to_string(index) + "].linear", l.linear);
							shader.setFloat("lights[" + std::to_string(index) + "].quadratic", l.quadratic);
							break;
						}
						case LightType::LIGHT_SPOT: {
							shader.setVec3("lights[" + std::to_string(index) + "].position", l.position);
							shader.setVec3("lights[" + std::to_string(index) + "].direction", l.direction);
							shader.setFloat("lights[" + std::to_string(index) + "].constant", l.constant);
							shader.setFloat("lights[" + std::to_string(index) + "].linear", l.linear);
							shader.setFloat("lights[" + std::to_string(index) + "].quadratic", l.quadratic);
							shader.setFloat("lights[" + std::to_string(index) + "].cutOff", l.cutoff);
							shader.setFloat("lights[" + std::to_string(index) + "].outerCutoff", l.outerCutoff);
							break;
						}
					}
				}
			}
		} // namespace ecs

		namespace transform {
			void updateLightPosition(const u32 &id, const vec3 &pos) {
				switch (const auto l = EntityManager::instance()->getLightFromId(id); l->getLight()->type) {
					case LIGHT_DIRECTIONAL: {
						break;
					}
					case LIGHT_POINT: {
						auto cast = std::static_pointer_cast<PointLight>(l->getLight());
						cast->position = pos;
						if (cast->showCaster) {
							auto t = EntityManager::instance()->getEntityComponent<Transform>(l->getCasterId());
							if (t != nullptr) {
								t->setPosition(pos);
							}
						}
						break;
					}
					case LIGHT_SPOT: {
						auto cast = std::static_pointer_cast<SpotLight>(l->getLight());
						cast->position = pos;
						if (cast->showCaster) {
							auto t = EntityManager::instance()->getEntityComponent<Transform>(l->getCasterId());
							if (t != nullptr) {
								t->setPosition(pos);
							}
						}
						break;
					}
					default: {
						std::cerr << "Invalid Light Type\n";
						break;
					}
				}
			}

			void updateEntityPosition(u32 id, const vec3 &pos) {
				auto em = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (em != nullptr) {
					em->addPosition(pos);
				}
			}

			void updateEntityRotation(u32 id, const vec3 &rot) {
				auto em = EntityManager::instance()->getEntityComponent<Transform>(id);
				if (em != nullptr)
					em->setRotation(rot);
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
				shader->setMat4("model", model->getModelMatrix());

				RenderApi::instance()->getRenderer()->drawArraysTriangles(vao, mesh->vertices.size());
				vao.unbind();
			}

			void drawElementIndexed(u32 id) {
				const auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
				const auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
				const auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id)->shader.get();

				shader->use();
				shader->setMat4("model", model->getModelMatrix());

				RenderApi::instance()->getRenderer()->drawElementsTriangles(mesh->vao, mesh->indices.size());
			}

			void drawAllInstanced() {
				RenderApi::instance()->getRenderer()->drawIndexed();
			}

			void drawAllMeshes() {
				const auto meshes = EntityManager::instance()->getEntitiesFromComponent<Mesh>();
				const auto lights = ::bolt::systems::ecs::retrieveLightsData();
				for (const auto id : meshes) {
					const auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(id);
					const auto model = EntityManager::instance()->getEntityComponent<Transform>(id);
					auto shader = EntityManager::instance()->getEntityComponent<ShaderComponent>(id);
					if (shader == nullptr) {
						// use default shader
						const auto s = RenderApi::instance()->getRenderer()->getDefaultShader();
						BT_ASSERT(s != nullptr);
						const auto mask = s->getMask();
						s->use();
						s->setMat4("model", model->getModelMatrix());

						// If shader implements lights, send light informations
						if (mask & ShaderConfig::shader_lights) {
							systems::ecs::sendLightData(*s);
							s->setInt("lightsCount", EntityManager::instance()->getLightsCount());
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
						shader->shader->setMat4("model", model->getModelMatrix());
					}

					mesh->render.call();
				}

				// draw all instanced primitives
				drawAllInstanced();
			}
		} // namespace render
	} // namespace systems

} // namespace bolt
