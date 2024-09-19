#include "MeshFactory.hpp"
#include <iostream>
#include <memory>

#include "../ECS/EntityManager.hpp"

#include "Buffer/GlVertexArray.hpp"
#include "Buffer/GlVertexBuffer.hpp"
#include "MeshVertices.hpp"

namespace Bolt {
	namespace factory {
		namespace mesh {

			void createEmptyCubeMesh(const u32 &id, config::MeshConfig config, vec4 color) {
				auto em = EntityManager::instance();
				Shared<Mesh> comp;

				// basic components added
				if (!em->entityHasComponent<Transform>(id))
					em->addComponent<Transform>(id);

				if (!em->entityHasComponent<Mesh>(id)) {
					comp = em->addComponent<Mesh>(id);
					comp->vao = CreateShared<GlVertexArray>();
					comp->vbo_g = CreateShared<GlVertexBuffer>();
                    comp->colorComponent = CreateUnique<Color>();
					comp->colorComponent->vbo_c = CreateShared<GlVertexBuffer>();
				}
				else
					comp = em->getEntityComponent<Mesh>(id);

				// preparing buffers
				comp->vao->onAttach();
				comp->vbo_g->onAttach();
				comp->colorComponent->vbo_c->onAttach();
				comp->vao->bind();
				comp->vbo_g->setup(cubeGeometry, sizeof(cubeGeometry), 0);
				comp->vao->linkAttribFast(0, 3, 0, 3 * sizeof(float), 0);

				auto colors = getColorVector(sizeof(cubeGeometry) / sizeof(float) / 3, color);
                comp->colorComponent->colors = CreateUnique<std::vector<vec4>>(colors);
				comp->colorComponent->vbo_c->setup(*comp->colorComponent->colors, 0);
				comp->vao->linkAttribFast(1, 4, 0, 0, (void *)0);

				comp->instanced = true;
			}
		} // namespace mesh
	} // namespace factory
} // namespace Bolt
