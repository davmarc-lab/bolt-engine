#include "GlRenderer.hpp"

#include "../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	void GlRenderer::onAttach() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void GlRenderer::drawArrays(const VertexArray &vao, const u32 &mode, const i32 &first, const i32 &count) {
		vao.bind();
		glDrawArrays(mode, first, count);
	}

	void GlRenderer::drawElements(const VertexArray &vao, const u32 &mode, const i32 &count, const u32 &type, const void *indices) {
		vao.bind();
		glDrawElements(mode, count, type, indices);
	}

	void GlRenderer::drawArraysLines(const VertexArray &vao, const i32 &count, const i32 &first) {
		this->drawArrays(vao, GL_LINES, first, count);
	}

	void GlRenderer::drawElementsLines(const VertexArray &vao, const i32 &count) {
		this->drawElements(vao, GL_LINES, count, GL_UNSIGNED_INT, nullptr);
	}

	void GlRenderer::drawArraysTriangles(const VertexArray &vao, const i32 &count, const i32 &first) {
		this->drawArrays(vao, GL_TRIANGLES, first, count);
	}

	void GlRenderer::drawElementsTriangles(const VertexArray &vao, const i32 &count) {
		this->drawElements(vao, GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
