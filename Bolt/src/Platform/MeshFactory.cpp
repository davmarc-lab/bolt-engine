#include "MeshFactory.hpp"

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
				if (!em->entityHasComponent<Mesh>(id))
					comp = em->addComponent<Mesh>(id);
				else
					comp = em->getEntityComponent<Mesh>(id);

				// preparing buffers

				// maybe in the draw func i should cast
				auto vao = static_cast<GlVertexArray &>(comp->vao);
				auto vbo_g = static_cast<GlVertexBuffer &>(comp->vbo_g);
				vao.onAttach();
				vbo_g.onAttach();
				vao.bind();
				vbo_g.setup(cubeGeometry, sizeof(cubeGeometry), 0);
				vao.linkAttribFast(0, 3, 0, 3 * sizeof(float), 0);

				comp->instanced = true;
			}
		} // namespace mesh
	} // namespace factory
} // namespace Bolt
