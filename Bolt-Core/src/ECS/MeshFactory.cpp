#include "../../include/Platform/MeshFactory.hpp"

#include <memory>

#include "../../include/ECS/EntityManager.hpp"
#include "../../include/ECS/System.hpp"

#include "../../include/Graphic/Buffer/VertexArray.hpp"
#include "../../include/Graphic/Buffer/VertexBuffer.hpp"
#include "../../include/Platform/MeshVertices.hpp"

#include "../../include/Graphic/Shader/Shader.hpp"

namespace bolt {
	namespace factory {
		namespace mesh {
			void createCustomMesh(const u32 &id, config::MeshConfig config, config::MeshShape shape) {
				auto em = EntityManager::instance();
				Shared<Mesh> comp;

				// basic components added
				if (!em->entityHasComponent<Transform>(id))
					em->addComponent<Transform>(id);

				if (!em->entityHasComponent<Mesh>(id)) {
					comp = em->addComponent<Mesh>(id);

					if (shape == config::shape_cube) {
						comp->vertices = cubeGeometry;

						if (config & config::mesh_colors) {
							auto colors = getColorVector(cubeGeometry.size(), vec4(1, 1, 1, 1));
							comp->colorComponent.colors = std::vector<vec4>(colors);
						}

						if (config & config::mesh_texture) {
							comp->texCoord = cubeTexCoord;
						}
					}

					if (shape == config::shape_square) {
						comp->vertices = squareGeometry;

						if (config & config::mesh_colors) {
							auto colors = getColorVector(squareGeometry.size(), vec4(1, 1, 1, 1));
							comp->colorComponent.colors = std::vector(colors);
						}

						if (config & config::mesh_texture) {
							comp->texCoord = squareTexCoord;
						}
					}

					if (shape == config::shape_circle) {
						auto info = getCircleVertices({0, 0}, {1, 1}, 40);
						comp->vertices = info.vertices;
						comp->colorComponent.colors = info.colors;
					}

					// shader
					auto shader = em->addComponent<ShaderComponent>(id);
					shader = CreateShared<ShaderComponent>();
				} else
					comp = em->getEntityComponent<Mesh>(id);

				// init mesh
			}

			void initCustomMesh(const u32 &id, config::MeshConfig config, config::MeshShape shape) {
				auto em = EntityManager::instance();
				if (!em->entityHasComponent<Mesh>(id))
					return;

				auto comp = em->getEntityComponent<Mesh>(id);
				comp->vao.onAttach();
				comp->vbo_g.onAttach();
				comp->vao.bind();

				comp->vbo_g.setup(comp->vertices, 0);
				comp->vao.linkAttribFast(0, 3, 0, false, 0, 0);

				if (config & config::mesh_colors) {
					comp->colorComponent.vbo_c.onAttach();
					comp->colorComponent.vbo_c.setup(comp->colorComponent.colors, 0);
					comp->vao.linkAttribFast(1, 4, 0, false, 0, 0);
				}

				if (config & config::mesh_texture) {
					comp->vbo_t.onAttach();
					comp->vbo_t.setup(comp->texCoord, 0);
					comp->vao.linkAttribFast(2, 2, 0, false, 0, 0);
				}

				if (config & config::mesh_indices) {
					comp->ebo.onAttach();
				}

				const auto shader = em->getEntityComponent<ShaderComponent>(id);
				auto vert = Application::getSceneType() == scene::SCENE_3D ? "shader/defaultPerspVertShader.glsl" : "shader/defaultOrthoVertShader.glsl";
				shader->shader = CreateUnique<ShaderProgram>(vert, "shader/defaultFragShader.glsl");
				shader->shader->createShaderProgram();

				// render
				auto vao = comp->vao;
				auto size = comp->vertices.size();

				if (shape == config::shape_square || shape == config::shape_cube) {
					comp->render.setCall([vao, size]() {
						RenderApi::instance()->getRenderer()->drawArraysTriangles(vao, size);
					});
				} else if (shape == config::shape_circle) {
					comp->render.setCall([vao, size]() {
						RenderApi::instance()->getRenderer()->drawArraysTriangleFan(vao, size);
					});
				}

				comp->instanced = true;
			}

			void instanceMesh(const u32 &id, const MeshHelper &helper) {
				if (helper.vertex.empty()) {
					// log
					std::cout << "Empty vertex. Mesh not created\n";
					return;
				}

				const auto em = EntityManager::instance();
				Shared<Mesh> mesh;
				if (!em->entityHasComponent<Mesh>(id))
					mesh = em->addComponent<Mesh>(id);
				else
					mesh = em->getEntityComponent<Mesh>(id);

				mesh->vao.onAttach();
				mesh->vao.bind();

				mesh->vertices = std::move(helper.vertex);
				mesh->vbo_g.onAttach();
				mesh->vbo_g.setup(mesh->vertices, 0);
				mesh->vao.linkAttribFast(0, 3, GL_FLOAT, false, 0, 0);

				if (!helper.colors.empty()) {
					mesh->colorComponent.colors = std::move(helper.colors);
				} else {
					for (auto v : mesh->vertices) {
						mesh->colorComponent.colors.push_back({0, 0, 0, 1});
					}
				}
				mesh->colorComponent.vbo_c.onAttach();
				mesh->colorComponent.vbo_c.setup(mesh->colorComponent.colors, 0);
				mesh->vao.linkAttribFast(1, 4, GL_FLOAT, false, 0, 0);

				if (!helper.index.empty()) {
					// init ebo
					mesh->indices = std::move(helper.index);
				}

				if (!helper.texCoords.empty()) {
					mesh->texCoord = std::move(helper.texCoords);
					mesh->vbo_t.onAttach();
					mesh->vbo_t.setup(mesh->texCoord, 0);
					mesh->vao.linkAttribFast(2, 2, GL_FLOAT, false, 0, 0);
				}

				if (!helper.normals.empty()) {
					auto norm = em->addComponent<NormalsComponent>(id);
					norm->normals = std::move(helper.normals);
					norm->vbo_n.onAttach();
					norm->vbo_n.setup(norm->normals, 0);
					mesh->vao.linkAttribFast(3, 3, GL_FLOAT, false, 0, 0);
				}

				if (!em->entityHasComponent<Transform>(id)) {
					const auto t = em->addComponent<Transform>(id);
					t->setPosition(helper.position);
					t->setScale(helper.scale);
					t->setRotation(helper.rotation);
				}

				// render
				auto vao = mesh->vao;
				auto mode = helper.renderInfo.mode;
				// TODO: missing error handling if parameters are not set of RenderHelper
				switch (helper.renderInfo.mode) {
					case RenderType::render_arrays: {
						auto first = helper.renderInfo.first;
						auto size = mesh->vertices.size();
						mesh->render.setCall([vao, mode, first, size]() {
							RenderApi::instance()->getRenderer()->drawArrays(vao, mode, first, size);
						});
						break;
					}
					case RenderType::render_elements: {
						auto size = mesh->indices.size();
						mesh->render.setCall([vao, mode, size]() {
							RenderApi::instance()->getRenderer()->drawElements(vao, mode, size, GL_UNSIGNED_INT);
						});
						break;
					}
					case RenderType::render_instance: {
						std::cout << "Not implemented yet.\n";
						break;
					}
				}
				mesh->instanced = true;
			}

		} // namespace mesh

	} // namespace factory

} // namespace bolt
