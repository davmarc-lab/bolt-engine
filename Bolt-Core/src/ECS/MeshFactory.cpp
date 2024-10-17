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

					for (int i = 0; i < sizeof(cubeGeometry) / (sizeof(cubeGeometry[0])); i += 3) {
						comp->vertices.push_back(vec3(cubeGeometry[i], cubeGeometry[i + 1], cubeGeometry[i + 3]));
					}

					auto colors = getColorVector(sizeof(cubeGeometry) / sizeof(float) / 3, vec4(0, 0, 0, 1));
					comp->colorComponent.colors = std::vector<vec4>(colors);

					// shader
					auto shader = em->addComponent<ShaderComponent>(id);
					shader = CreateShared<ShaderComponent>();

					// render
				}
				else
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

				comp->vbo_g.setup(cubeGeometry, sizeof(cubeGeometry), 0);
				comp->vao.linkAttribFast(0, 3, 0, false, 3 * sizeof(float), 0);

				if (config & config::mesh_colors) {
					comp->colorComponent.vbo_c.onAttach();
					comp->colorComponent.vbo_c.setup(comp->colorComponent.colors, 0);
					comp->vao.linkAttribFast(1, 4, 0, false, 0, (void *)0);
				}

				if (config & config::mesh_texture) {
					comp->vbo_t.onAttach();
					comp->vbo_t.setup(cubeTexCoord, sizeof(cubeTexCoord), 0);
					comp->vao.linkAttribFast(2, 2, 0, false, 2 * sizeof(float), 0);
				}

				if (config & config::mesh_indices) {
					comp->ebo.onAttach();
				}

				auto shader = em->getEntityComponent<ShaderComponent>(id);
				shader->shader = CreateUnique<ShaderProgram>("shader/defaultPerspVertShader.glsl", "shader/defaultFragShader.glsl", "shader/geometryShader.glsl");
				shader->shader->createShaderProgram();

				// render
				auto vao = comp->vao;
				auto size = comp->vertices.size();

				comp->render.setCall([vao, size]() {
					RenderApi::instance()->getRenderer()->drawArraysTriangles(vao, size);
				});

				comp->instanced = true;
			}

			void createEmptySquare(const u32 &id, config::MeshConfig) {
				auto em = EntityManager::instance();
				Shared<Mesh> comp;

				// basic components added
				if (!em->entityHasComponent<Transform>(id))
					em->addComponent<Transform>(id);

				if (!em->entityHasComponent<Mesh>(id)) {
					comp = em->addComponent<Mesh>(id);

					for (int i = 0; i < sizeof(squareGeometry) / (sizeof(squareGeometry[0])); i += 3) {
						comp->vertices.push_back(vec3(squareGeometry[i], squareGeometry[i + 1], squareGeometry[i + 3]));
					}
					auto colors = getColorVector(sizeof(squareGeometry) / sizeof(float) / 3, vec4(0, 0, 0, 1));
					comp->colorComponent.colors = std::vector<vec4>(colors);

					// shader
					auto shader = em->addComponent<ShaderComponent>(id);
					shader = CreateShared<ShaderComponent>();

					// render
				}
				else
					comp = em->getEntityComponent<Mesh>(id);
			}

			void initSquareMesh(const u32 &id, config::MeshConfig config) {
				auto em = EntityManager::instance();
				if (!em->entityHasComponent<Mesh>(id))
					return;

				auto comp = em->getEntityComponent<Mesh>(id);
				comp->vao.onAttach();
				comp->vbo_g.onAttach();
				comp->colorComponent.vbo_c.onAttach();
				comp->vbo_t.onAttach();
				comp->ebo.onAttach();
				comp->vao.bind();

				comp->vbo_g.setup(squareGeometry, sizeof(squareGeometry), 0);
				comp->vao.linkAttribFast(0, 3, 0, false, 3 * sizeof(float), 0);

				comp->colorComponent.vbo_c.setup(comp->colorComponent.colors, 0);
				comp->vao.linkAttribFast(1, 4, 0, false, 0, (void *)0);

				comp->vbo_t.setup(squareTexCoord, sizeof(squareTexCoord), 0);
				comp->vao.linkAttribFast(2, 2, 0, false, 2 * sizeof(float), 0);

				auto shader = em->getEntityComponent<ShaderComponent>(id);
				shader->shader = CreateUnique<ShaderProgram>("shader/defaultOrthoVertShader.glsl", "shader/defaultFragShader.glsl");
				shader->shader->createShaderProgram();

				// render
				auto vao = comp->vao;
				auto size = comp->vertices.size();

				comp->render.setCall([vao, size]() {
					RenderApi::instance()->getRenderer()->drawArraysTriangles(vao, size);
				});

				comp->instanced = true;
			}

		} // namespace mesh
	} // namespace factory
} // namespace bolt
