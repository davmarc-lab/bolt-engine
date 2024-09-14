#include "GlVertexArray.hpp"
#include <memory>

#include "../../../dependencies/glad/include/glad/glad.h"
#include "GlVertexBuffer.hpp"

namespace Bolt {
	void GlVertexArray::onAttach() {
		glGenVertexArrays(1, &this->m_id);
	}

	void GlVertexArray::onDetach() {
		glDeleteVertexArrays(1, &this->m_id);
	}

	void GlVertexArray::bind() const {
		glBindVertexArray(this->m_id);
	}

	void GlVertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void GlVertexArray::linkVertexBuffer(const VertexBuffer& vbo, const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize) const {
		this->bind();
        static_cast<const GlVertexBuffer&>(vbo).bind();
		glVertexAttribPointer(layout, size, type == 0 ? GL_FLOAT : type, normalize ? GL_TRUE : GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
	}

	void GlVertexArray::linkAttribFast(const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize) const {
		glVertexAttribPointer(layout, size, type == 0 ? GL_FLOAT : type, normalize ? GL_TRUE : GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
	}
}
