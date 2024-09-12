#include "GlRenderBuffer.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	void GlRenderBuffer::onAttach() {
        glGenRenderbuffers(1, &this->m_id);
    }

	void GlRenderBuffer::onDetach() { glDeleteRenderbuffers(1, &this->m_id); }

	void GlRenderBuffer::bind() const { glBindRenderbuffer(GL_RENDERBUFFER, this->m_id); }

	void GlRenderBuffer::unbind() const { glBindRenderbuffer(GL_RENDERBUFFER, 0); }
} // namespace Bolt
