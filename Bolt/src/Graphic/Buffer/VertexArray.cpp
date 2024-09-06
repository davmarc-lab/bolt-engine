#include "VertexArray.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	void VertexArray::onAttach() {
		glGenVertexArrays(1, &this->m_id);
	}

	void VertexArray::onDetach() {
		glDeleteVertexArrays(1, &this->m_id);
	}

	void VertexArray::bind() const {
		glBindVertexArray(this->m_id);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::linkVertexBuffer(const VertexBuffer &vbo, const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize) const {
		this->bind();
		vbo.bind();
		glVertexAttribPointer(layout, size, type, normalize ? GL_TRUE : GL_FALSE, stride, offset);
	}

	void VertexArray::linkAttribFast(const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize) const {
		glVertexAttribPointer(layout, size, type, normalize ? GL_TRUE : GL_FALSE, stride, offset);
	}

}
