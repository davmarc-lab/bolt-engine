#include "GlElementBuffer.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {

	GlElementBuffer::~GlElementBuffer() {
		if (this->m_id)
			glDeleteBuffers(1, &this->m_id);
	}

	void GlElementBuffer::onAttach() { glGenBuffers(1, &this->m_id); }

	void GlElementBuffer::onDetach() { glDeleteBuffers(1, &this->m_id); }

	void GlElementBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
	}

	void GlElementBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GlElementBuffer::setup(const f32 *indices, const i64 &size, const u32 &usage) const {
		this->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage == 0 ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void GlElementBuffer::setup(const T *indices, const i64 &size, const u32 &usage) {
		this->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage == 0 ? GL_STATIC_DRAW : usage);
	}

	template <typename T>
	void GlElementBuffer::setup(const std::vector<T> &indices, const u32 &usage) {
		this->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(T), indices.data(), usage);
	}

} // namespace Bolt
