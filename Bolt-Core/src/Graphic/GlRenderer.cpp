#include "../../include/Graphic/Renderer/Renderer.hpp"

#include "../../../Bolt-Graphics/include/glad/glad.h"

#include "../../include/Application/Application.hpp"
#include "../../include/Graphic/Buffer/VertexArray.hpp"

namespace bolt {
	void Renderer::onAttach() {
		// create the default shader
		auto vert = Application::getSceneType() == scene::SCENE_3D ? "shader/defaultPerspVertShader.glsl" : "shader/defaultOrthoVertShader.glsl";
		this->m_shader = CreateUnique<ShaderProgram>(vert, "shader/defaultFragShader.glsl", defaultShaderMask);
		this->m_shader->createShaderProgram();

        // create light caster shader
        this->m_casterShader = CreateUnique<ShaderProgram>("shader/lightcasterVert.glsl", "shader/lightcasterFrag.glsl", casterShaderMask);
        this->m_casterShader->createShaderProgram();
	}

	void Renderer::onDetach() {}

	ShaderProgram *Renderer::getDefaultShader() const { return this->m_shader.get(); }

	ShaderProgram *Renderer::getCastersShader() const { return this->m_casterShader.get(); }

	void Renderer::drawArrays(const VertexArray &vao, const u32 &mode, const i32 &first, const size_t &count) {
		vao.bind();
		glDrawArrays(mode, first, static_cast<i32>(count));
	}

	void Renderer::drawElements(const VertexArray &vao, const u32 &mode, const size_t &count, const u32 &type, const void *indices) {
		vao.bind();
		glDrawElements(mode, static_cast<i32>(count), type, indices);
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
} // namespace bolt
