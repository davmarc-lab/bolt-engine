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
			void instanceMesh(const u32 &id, const MeshHelper &helper) {
				if (helper.vertex.empty()) {
					// log
					std::cout << "Empty vertex. Mesh not created\n";
					return;
				}

				const auto em = EntityManager::instance();

				if (!helper.name.empty()) em->setEntityName(id, helper.name);
				
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
				mesh->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, 0);

				if (!helper.colors.empty()) {
					mesh->colorComponent.colors = std::move(helper.colors);
				} else {
					for (auto v : mesh->vertices) {
						mesh->colorComponent.colors.push_back({1, 1, 1, 1});
					}
				}
				mesh->colorComponent.vbo_c.onAttach();
				mesh->colorComponent.vbo_c.setup(mesh->colorComponent.colors, 0);
				mesh->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, 0);

				if (!helper.index.empty()) {
					// init ebo
					mesh->indices = std::move(helper.index);
				}

				if (!helper.texCoords.empty()) {
					mesh->texCoord = std::move(helper.texCoords);
					mesh->vbo_t.onAttach();
					mesh->vbo_t.setup(mesh->texCoord, 0);
					mesh->vao.linkAttribFast(SHADER_TEXCOORDS_LOCATION, 2, GL_FLOAT, false, 0, 0);
				}

				if (!helper.normals.empty()) {
					auto norm = em->addComponent<NormalsComponent>(id);
					norm->normals = std::move(helper.normals);
					norm->vbo_n.onAttach();
					norm->vbo_n.setup(norm->normals, 0);
					mesh->vao.linkAttribFast(SHADER_NORMAL_LOCATION, 3, GL_FLOAT, false, 0, 0);
				}

				if (!em->entityHasComponent<Transform>(id)) {
					const auto t = em->addComponent<Transform>(id);
					t->setPosition(helper.position);
					t->setScale(helper.scale);
					t->setRotation(helper.rotation);
				}
				if (!em->entityHasComponent<Material>(id)) {
					const auto t = em->addComponent<Material>(id);
				}

				// render
				auto vao = mesh->vao;
				auto mode = helper.renderInfo.mode;
				// TODO: missing error handling if parameters are not set of RenderHelper
				switch (helper.renderInfo.type) {
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
