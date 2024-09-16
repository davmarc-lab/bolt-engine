#include "GlFrameBuffer.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	void GlFrameBuffer::onAttach() {
		glGenFramebuffers(1, &this->m_id);
	}

	void GlFrameBuffer::onDetach() { glDeleteFramebuffers(1, &this->m_id); }

	void GlFrameBuffer::bind() const { glBindFramebuffer(this->m_config.operation, this->m_id); }

	void GlFrameBuffer::unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	void GlFrameBuffer::attachTexture(const TextureAttach &attach) {
		u32 id;
		glGenTextures(1, &id);
		// add the textureAttach to the vector
		this->m_texturesAttachement.push_back({id,
			attach.target,
			attach.level,
			attach.internalFormat,
			attach.width,
			attach.height,
			attach.border,
			attach.format,
			attach.dataType,
			attach.data});
		glBindTexture(attach.target, id);

		glTexImage2D(attach.target, attach.level, static_cast<i32>(attach.internalFormat), attach.width, attach.height, attach.border, attach.format, attach.dataType, attach.data);

        glTexParameteri(attach.target, texture::opengl::pname::TEXTURE_MAG_FILTER, texture::opengl::pvalue::LINEAR);
        glTexParameteri(attach.target, texture::opengl::pname::TEXTURE_MIN_FILTER, texture::opengl::pvalue::LINEAR);

        glFramebufferTexture2D(this->m_config.operation, GL_COLOR_ATTACHMENT0, attach.target, id, attach.level);
	}

} // namespace Bolt
