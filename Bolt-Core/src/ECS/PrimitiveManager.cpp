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
		s_cube.vao.onAttach();
		s_cube.vao.bind();

		s_cube.vertices = factory::mesh::cubeGeometry;
		s_cube.vbo_g.onAttach();
		s_cube.vbo_g.setup(s_cube.vertices, 0);
		s_cube.vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, 0);

		s_cube.colorComponent.colors = factory::mesh::getColorVector(s_cube.vertices.size(), {1, 1, 1, 1});
		s_cube.colorComponent.vbo_c.onAttach();
		s_cube.colorComponent.vbo_c.setup(s_cube.colorComponent.colors, 0);
		s_cube.vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, 0);

		auto vao = s_cube.vao;
		auto size = s_cube.vertices.size();
		s_cube.render.setCall([vao, size]() {
			RenderApi::instance()->getRenderer()->drawArrays(vao, GL_TRIANGLES, 0, size);
		});

		// create cone

		// create sphere
	}

    u32 PrimitiveManager::addCubePrimitive(const vec3& pos, const vec3& scale, const vec3& rot, const vec4& color) {
        auto em = EntityManager::instance();
        auto id = em->createEntity();

        Shared<Mesh> comp = CreateShared<Mesh>(s_cube);
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
