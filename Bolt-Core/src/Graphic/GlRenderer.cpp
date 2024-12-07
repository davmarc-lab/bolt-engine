#include <iostream>
#include "../../include/Graphic/Renderer/Renderer.hpp"

#include "../../../Bolt-Graphics/include/glad/glad.h"

#include "../../include/Application/Application.hpp"
#include "../../include/Graphic/Buffer/VertexArray.hpp"

#include "../../include/Graphic/Camera/Camera.hpp"

#include "../../include/ECS/System.hpp"

#include "../../include/Platform/MeshVertices.hpp"

namespace bolt {
	void Renderer::onAttach() {
		// create the default shader
		auto vert = Application::getSceneType() == scene::SCENE_3D ? "shader/defaultPerspVertShader.glsl" : "shader/defaultOrthoVertShader.glsl";
		this->m_shader = CreateShared<ShaderProgram>(vert, "shader/defaultFragShader.glsl", defaultShaderMask);
		BT_ASSERT(this->m_shader != nullptr);
		this->m_shader->createShaderProgram();
		BT_ASSERT(this->m_shader->getId() != 0);

		// create light caster shader
		this->m_casterShader = CreateUnique<ShaderProgram>("shader/lightcasterVert.glsl", "shader/lightcasterFrag.glsl", casterShaderMask);
		BT_ASSERT(this->m_casterShader != nullptr);
		this->m_casterShader->createShaderProgram();
		BT_ASSERT(this->m_casterShader->getId() != 0);

		// create instanced shader
		this->m_instancedShader = CreateUnique<ShaderProgram>("shader/instancedVertShader.glsl", "shader/instancedFragShader.glsl", casterShaderMask);
		this->m_instancedShader->createShaderProgram();

		// create Cube primitive
		this->m_cube.vao.onAttach();
		this->m_cube.vao.bind();

		this->m_cube.vbo_g.onAttach();
		this->m_cube.vbo_g.setup(factory::mesh::cubeGeometry, 0);
		this->m_cube.vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, 0);

		this->m_cube.vbo_t.onAttach();
		this->m_cube.vbo_t.setup(factory::mesh::cubeTexCoord, 0);
		this->m_cube.vao.linkAttribFast(SHADER_TEXCOORDS_LOCATION, 2, GL_FLOAT, false, 0, 0);

		this->m_cube.normals.vbo_n.onAttach();
		this->m_cube.normals.vbo_n.setup(factory::mesh::cubeNormals, 0);
		this->m_cube.vao.linkAttribFast(SHADER_NORMAL_LOCATION, 3, GL_FLOAT, false, 0, 0);

		this->m_cube.vbo_mi.onAttach();
		this->m_cube.vbo_co.onAttach();

		EventDispatcher::instance()->subscribe(events::loop::LoopBeforeRender, [this](auto p) {
			this->m_tracker.drawCalls = 0;
		});
	}

	void Renderer::onDetach() {}

	Shared<ShaderProgram> Renderer::getDefaultShader() const { return this->m_shader; }

	ShaderProgram *Renderer::getCastersShader() const { return this->m_casterShader.get(); }

	void Renderer::drawCube(const vec3 &pos, const vec3 &scale, const vec3 &rotation, const vec4 &color) {
		auto base = mat4(1);
		auto model = translate(base, pos) * glm::scale(base, scale);
		this->drawCube(model, color);
	}

	void Renderer::drawCube(const mat4 &transform, const vec4 &color) {
		this->m_tracker.cubes++;
		this->m_cube.modelInstance.push_back(transform);
		BT_ASSERT(this->m_cube.modelInstance.size() == this->m_tracker.cubes);

		this->m_cube.colorOffset.push_back(color);
		BT_ASSERT(this->m_cube.colorOffset.size() == this->m_cube.modelInstance.size());

		// sends the information in the buffer reserved for model matrices
		this->m_cube.vao.bind();
		this->m_cube.vbo_mi.setup(this->m_cube.modelInstance, 0);
		// a mat4 in shaders uses four vec4, so we need to link 4 sequential locations
		this->m_cube.vao.linkAttribFast(SHADER_MODEL_OFFSET_LOCATION, 4, GL_FLOAT, false, 4 * sizeof(vec4), 0);
		this->m_cube.vao.linkAttribFast(SHADER_MODEL_OFFSET_LOCATION + 1, 4, GL_FLOAT, false, 4 * sizeof(vec4), (void *)(1 * sizeof(vec4)));
		this->m_cube.vao.linkAttribFast(SHADER_MODEL_OFFSET_LOCATION + 2, 4, GL_FLOAT, false, 4 * sizeof(vec4), (void *)(2 * sizeof(vec4)));
		this->m_cube.vao.linkAttribFast(SHADER_MODEL_OFFSET_LOCATION + 3, 4, GL_FLOAT, false, 4 * sizeof(vec4), (void *)(3 * sizeof(vec4)));
		glVertexAttribDivisor(SHADER_MODEL_OFFSET_LOCATION, 1);
		glVertexAttribDivisor(SHADER_MODEL_OFFSET_LOCATION + 1, 1);
		glVertexAttribDivisor(SHADER_MODEL_OFFSET_LOCATION + 2, 1);
		glVertexAttribDivisor(SHADER_MODEL_OFFSET_LOCATION + 3, 1);

		this->m_cube.vbo_co.setup(this->m_cube.colorOffset, 0);
		this->m_cube.vao.linkAttribFast(SHADER_COLOR_OFFSET_LOCATION, 4, GL_FLOAT, false, 0, 0);
		glVertexAttribDivisor(SHADER_COLOR_OFFSET_LOCATION, 1);
	}

	void Renderer::drawArrays(const VertexArray &vao, const u32 &mode, const i32 &first, const size_t &count) {
		vao.bind();
		glDrawArrays(mode, first, static_cast<i32>(count));
		this->m_tracker.drawCalls++;
	}

	void Renderer::drawElements(const VertexArray &vao, const u32 &mode, const size_t &count, const u32 &type, const void *indices) {
		vao.bind();
		glDrawElements(mode, static_cast<i32>(count), type, indices);
		this->m_tracker.drawCalls++;
	}

	void Renderer::drawArraysLines(const VertexArray &vao, const size_t &count, const i32 &first) {
		this->drawArrays(vao, GL_LINES, first, count);
	}

	void Renderer::drawElementsLines(const VertexArray &vao, const size_t &count) {
		this->drawElements(vao, GL_LINES, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawArraysTriangles(const VertexArray &vao, const size_t &count, const i32 &first) {
		this->drawArrays(vao, GL_TRIANGLES, first, count);
	}

	void Renderer::drawArraysTriangleFan(const VertexArray &vao, const size_t &count, const i32 &first) {
		this->drawArrays(vao, GL_TRIANGLE_FAN, first, count);
	}

	void Renderer::drawElementsTriangles(const VertexArray &vao, const size_t &count) {
		this->drawElements(vao, GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	// I don't like this
	void Renderer::drawIndexed() {
		if (this->m_tracker.cubes) {
			this->m_instancedShader->use();
			if (EntityManager::instance()->getLightsCount()) {
				systems::ecs::sendLightData(*this->m_instancedShader.get());
				this->m_instancedShader->setInt("lightsCount", EntityManager::instance()->getLightsCount());
				this->m_instancedShader->setVec3("viewPos", standardCamera.getCameraPosition());
				Material mat{};
				this->m_instancedShader->setVec3("material.ambient", mat.ambient);
				this->m_instancedShader->setVec3("material.diffuse", mat.diffuse);
				this->m_instancedShader->setVec3("material.specular", mat.specular);
				this->m_instancedShader->setFloat("material.shininess", mat.shininess);
			}
			this->m_cube.vao.bind();
			glDrawArraysInstanced(GL_TRIANGLES, 0, factory::mesh::cubeGeometry.size(), this->m_tracker.cubes);
			this->m_tracker.drawCalls++;
		}
	}
} // namespace bolt
