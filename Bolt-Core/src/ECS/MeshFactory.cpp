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
						for (size_t i = 0; i < std::size(cubeGeometry); i += 3) {
							comp->vertices.emplace_back(cubeGeometry[i], cubeGeometry[i + 1], cubeGeometry[i + 2]);
						}

						if (config & config::mesh_colors) {
							auto colors = getColorVector(sizeof(cubeGeometry) / sizeof(float) / 3, vec4(1, 1, 1, 1));
							comp->colorComponent.colors = std::vector<vec4>(colors);
						}

						if (config & config::mesh_texture) {
							for (size_t i = 0; i < std::size(cubeTexCoord); i += 2) {
								comp->texCoord.emplace_back(cubeTexCoord[i], cubeTexCoord[i + 1]);
							}
						}
					}

					if (shape == config::shape_square) {
						for (size_t i = 0; i < std::size(squareGeometry); i += 3) {
							comp->vertices.emplace_back(squareGeometry[i], squareGeometry[i + 1], squareGeometry[i + 2]);
						}

						if (config & config::mesh_colors) {
							auto colors = getColorVector(sizeof(squareGeometry) / sizeof(float) / 3, vec4(1, 1, 1, 1));
							comp->colorComponent.colors = std::vector(colors);
						}

						if (config & config::mesh_texture) {
							for (size_t i = 0; i < std::size(squareTexCoord); i += 2) {
								comp->texCoord.emplace_back(squareTexCoord[i], squareTexCoord[i + 1]);
							}
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
		} // namespace mesh

	} // namespace factory

} // namespace bolt
