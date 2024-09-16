#include "GlTexture.hpp"
#include <cassert>

namespace Bolt {
	void GlTexture::onAttach() {
		glGenTextures(1, &this->m_id);
	}

	void GlTexture::onDetach() {
		glDeleteTextures(1, &this->m_id);
	}

	void GlTexture::bind() {
		// always activate the first texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(this->m_type, this->m_id);
	}

	void GlTexture::unbind() {}

	void GlTexture::setTexParameter(u32 target, u32 pname, u32 pval) {
		glTexParameteri(target, pname, pval);
		this->m_customParam = true;
	}

	void GlTexture::createTexture2D(u32 target, i32 level, u32 internalFormat, i32 width, i32 height, i32 border, u32 format, u32 dataType, void *data) {
		if (!this->m_customParam) {
            // bind default params
		}
		glTexImage2D(target, level, internalFormat, width, height, border, format, dataType, data);
		this->m_created = true;
	}

	void GlTexture::generateMipmap(u32 target) {
		assert(this->m_created);
		glGenerateMipmap(target);
	}
} // namespace Bolt
