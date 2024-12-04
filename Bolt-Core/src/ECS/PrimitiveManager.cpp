#include <iostream>
#include "../../include/ECS/PrimitivesManager.hpp"

#include "../../include/ECS/EntityManager.hpp"
#include "../../include/Core/RenderApi.hpp"
#include "../../include/Platform/MeshVertices.hpp"

#include "../../include/Graphics.hpp"

namespace bolt {

	PrimitiveManager::PrimitiveManager() {
		// create square

		// create triangle

		// create circle

		// create cube
		// this needs to implements indices
		this->m_cube.vao.onAttach();
		this->m_cube.vao.bind();

		this->m_cube.vertices = factory::mesh::cubeGeometry;
		this->m_cube.vbo_g.onAttach();
		this->m_cube.vbo_g.setup(this->m_cube.vertices, 0);
		this->m_cube.vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, 0);

		this->m_cube.colorComponent.colors = factory::mesh::getColorVector(this->m_cube.vertices.size(), {1, 1, 1, 1});
		this->m_cube.colorComponent.vbo_c.onAttach();
		this->m_cube.colorComponent.vbo_c.setup(this->m_cube.colorComponent.colors, 0);
		this->m_cube.vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, 0);

		auto vao = this->m_cube.vao;
		auto size = this->m_cube.vertices.size();
		this->m_cube.render.setCall([vao, size]() {
			RenderApi::instance()->getRenderer()->drawArrays(vao, GL_TRIANGLES, 0, size);
		});

		// create cone

		// create sphere
	}

    u32 PrimitiveManager::addCubePrimitive(const vec3& pos, const vec3& scale, const vec3& rot, const vec4& color) {
        auto em = EntityManager::instance();
        auto id = em->createEntity();

        Shared<Mesh> comp = CreateShared<Mesh>(this->m_cube);
        em->addComponent<Mesh>(id, comp);
		auto t = em->addComponent<Transform>(id);
		t->setPosition(pos);
		t->setScale(scale);
		t->setRotation(rot);

		std::cout << "This doesn't update the color\n";
		comp->colorComponent.colors = factory::mesh::getColorVector(comp->vertices.size(), color);
        return id;
    }


} // namespace bolt
