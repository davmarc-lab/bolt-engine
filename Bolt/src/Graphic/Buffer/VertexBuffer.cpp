#include "VertexBuffer.hpp"

#include <utility>

#include "../../../dependencies/glad/include/glad/glad.h"
#include "Buffer.hpp"

namespace Bolt {
	VertexBuffer::~VertexBuffer() {
		if (this->m_id)
			glDeleteBuffers(1, &this->m_id);
	}

	VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other) noexcept {
		if (this != &other) {
			if (this->m_id)
				glDeleteBuffers(1, &this->m_id);
			this->m_id = std::exchange(other.m_id, 0);
		}
		return *this;
	}

	void VertexBuffer::onAttach() { glGenBuffers(1, &this->m_id); }

	void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->m_id); }

	void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	void VertexBuffer::setup(const f32 *vertices, const i64 &size, const u32 &usage) {
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage == buffers::DEFAULT_USAGE ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void VertexBuffer::setup(const T *vertices, const i64 &size, const u32 &usage) {
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage == buffers::DEFAULT_USAGE ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void VertexBuffer::setup(const std::vector<T> &vertices, const u32 &usage) {
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), usage == buffers::DEFAULT_USAGE ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void VertexBuffer::setupSubData(const T *vertices, const i64 &size, const i64 &offset) {
		this->bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}

	template <typename T>
	void VertexBuffer::setupSubData(const std::vector<T> &vertices, const i64 &offset) {
		this->bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * sizeof(T), vertices.data());
	}
}
