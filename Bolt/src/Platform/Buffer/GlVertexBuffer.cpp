#include "GlVertexBuffer.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	GlVertexBuffer::~GlVertexBuffer() {
		if (this->m_id)
			glDeleteBuffers(1, &this->m_id);
	}

	void GlVertexBuffer::onAttach() { glGenBuffers(1, &this->m_id); }

	void GlVertexBuffer::onDetach() { glDeleteBuffers(1, &this->m_id); }

	void GlVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->m_id); }

	void GlVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	void GlVertexBuffer::setup(const f32 *vertices, const i64 &size, const u32 &usage) {
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage == 0 ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void GlVertexBuffer::setup(const T *vertices, const i64 &size, const u32 &usage) {
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage == 0 ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void GlVertexBuffer::setup(const std::vector<T> &vertices, const u32 &usage) {
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), usage == 0 ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void GlVertexBuffer::setupSubData(const T *vertices, const i64 &size, const i64 &offset) {
		this->bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}

	template <typename T>
	void GlVertexBuffer::setupSubData(const std::vector<T> &vertices, const i64 &offset) {
		this->bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * sizeof(T), vertices.data());
	}
}
