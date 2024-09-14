#include "MeshFactory.hpp"
#include <memory>

#include "../ECS/EntityManager.hpp"

#include "Buffer/GlVertexArray.hpp"
#include "Buffer/GlVertexBuffer.hpp"
#include "MeshVertices.hpp"

namespace Bolt {
	namespace factory {
		namespace mesh {

			void createEmptyCubeMesh(const u32 &id, config::MeshConfig config) {
				auto em = EntityManager::instance();
				std::shared_ptr<Mesh> comp;

				// basic components added
				if (!em->entityHasComponent<Transform>(id))
					em->addComponent<Transform>(id);
				if (!em->entityHasComponent<Mesh>(id)) {
					comp = em->addComponent<Mesh>(id);
                    comp->vao = std::make_shared<GlVertexArray>();
                    comp->vbo_g = std::make_shared<GlVertexBuffer>();
				} else
					comp = em->getEntityComponent<Mesh>(id);

				// preparing buffers
				comp->vao->onAttach();
				comp->vbo_g->onAttach();
				comp->vao->bind();
				comp->vbo_g->setup(cubeGeometry, sizeof(cubeGeometry), 0);
				comp->vao->linkAttribFast(0, 3, 0, 3 * sizeof(float), 0);

				comp->instanced = true;
			}
		} // namespace mesh
	} // namespace factory
} // namespace Bolt
