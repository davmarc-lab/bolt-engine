#include "ElementBuffer.hpp"

#include <utility>

#include "../../../dependencies/glad/include/glad/glad.h"
#include "Buffer.hpp"

namespace Bolt {
	ElementBuffer &ElementBuffer::operator=(ElementBuffer &&other) noexcept {
		if (this != &other) {
			if (this->m_id)
				glDeleteBuffers(1, &this->m_id);
			this->m_id = std::exchange(other.m_id, 0);
		}
		return *this;
	}

	ElementBuffer::~ElementBuffer() {
		if (this->m_id)
			glDeleteBuffers(1, &this->m_id);
	}

	void ElementBuffer::onAttach() { glGenBuffers(1, &this->m_id); }

	void ElementBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
	}

	void ElementBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ElementBuffer::setup(const f32 *indices, const i64 &size, const u32 &usage) const {
		this->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage == buffers::DEFAULT_USAGE ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void ElementBuffer::setup(const T *indices, const i64 &size, const u32 &usage) {
		this->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage == buffers::DEFAULT_USAGE ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void ElementBuffer::setup(const std::vector<T> &indices, const u32 &usage) {
		this->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(T), indices.data(), usage);
	}

} // namespace Bolt
