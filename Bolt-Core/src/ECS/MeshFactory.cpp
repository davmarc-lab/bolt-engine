#include "../../include/Platform/MeshFactory.hpp"

#include <iostream>
#include <memory>

#include "../../include/ECS/EntityManager.hpp"

#include "../../include/Graphic/Buffer/VertexArray.hpp"
#include "../../include/Graphic/Buffer/VertexBuffer.hpp"
#include "../../include/Platform/MeshVertices.hpp"

#include "../../include/Graphic/Shader/Shader.hpp"

namespace bolt {
	namespace factory {
		namespace mesh {

			void createEmptyCubeMesh(const u32& id, config::MeshConfig config, const vec4& color) {
				auto em = EntityManager::instance();
				Shared<Mesh> comp;

				// basic components added
				if (!em->entityHasComponent<Transform>(id))
					em->addComponent<Transform>(id);

				if (!em->entityHasComponent<Mesh>(id)) {
					comp = em->addComponent<Mesh>(id);
					comp->vao = CreateShared<VertexArray>();
					comp->vbo_g = CreateShared<VertexBuffer>();

					comp->colorComponent = CreateUnique<Color>();
					auto colors = getColorVector(sizeof(cubeGeometry) / sizeof(float) / 3, color);
					comp->colorComponent->colors = std::vector<vec4>(colors);
					comp->colorComponent->vbo_c = CreateShared<VertexBuffer>();

					comp->vbo_t = CreateShared<VertexBuffer>();

					// shader
					auto shader = em->addComponent<ShaderComponent>(id);
					shader = CreateShared<ShaderComponent>();
				}
				else
					comp = em->getEntityComponent<Mesh>(id);
			}

			void initMesh(u32 id, config::MeshConfig config) {
				auto em = EntityManager::instance();
				if (!em->entityHasComponent<Mesh>(id))
					return;

				auto comp = em->getEntityComponent<Mesh>(id);
				comp->vao->onAttach();
				comp->vbo_g->onAttach();
				comp->colorComponent->vbo_c->onAttach();
				comp->vbo_t->onAttach();
				comp->vao->bind();

				comp->vbo_g->setup(cubeGeometry, sizeof(cubeGeometry), 0);
				comp->vao->linkAttribFast(0, 3, 0, false, 3 * sizeof(float), 0);

				comp->colorComponent->vbo_c->setup(comp->colorComponent->colors, 0);
				comp->vao->linkAttribFast(1, 4, 0, false, 0, (void*)0);

				comp->vbo_t->setup(cubeTexCoord, sizeof(cubeTexCoord), 0);
				comp->vao->linkAttribFast(2, 2, 0, false, 2 * sizeof(float), 0);

				auto shader = em->getEntityComponent<ShaderComponent>(id);
				shader->shader = CreateUnique<ShaderProgram>("shader/defaultVertShader.glsl", "shader/defaultFragShader.glsl");
				shader->shader->createShaderProgram();

				comp->instanced = true;
			}
		} // namespace mesh
	} // namespace factory
} // namespace bolt
