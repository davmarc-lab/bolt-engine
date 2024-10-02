#include "../../../include/Graphic/Buffer/FrameBuffer.hpp"

#include "../../../../Bolt-Graphics/include/glad/glad.h"

#include <iostream>

namespace bolt {
	void FrameBuffer::onAttach() {
		glGenFramebuffers(1, &this->m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);

		//// create a color attachment texture
		//unsigned int textureColorbuffer;
		//glGenTextures(1, &textureColorbuffer);
		//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
		//// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		//unsigned int rbo;
		//glGenRenderbuffers(1, &rbo);
		//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1600, 900); // use a single renderbuffer object for both a depth AND stencil buffer.
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
		//// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		//	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		std::cout << "Change with Application/Window size!\n";
		this->m_textureAttach = Texture(texture::Parameters{GL_TEXTURE_2D, 0, GL_RGB, 0, GL_RGB, GL_UNSIGNED_BYTE}, 1600, 900);
		this->m_textureAttach.onAttach();

		this->m_textureAttach.bind();
		this->m_textureAttach.setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		this->m_textureAttach.setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		this->m_textureAttach.createTexture2D(NULL);

		glFramebufferTexture2D(this->m_config.operation, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_textureAttach.getId(), 0);
		this->m_textureAttach.unbind();

		this->m_renderBuffer = RenderBuffer(rbo::Config{
			GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, this->m_textureAttach.getWidth(), this->m_textureAttach.getHeight()
		});
		this->m_renderBuffer.onAttach();
		glFramebufferRenderbuffer(this->m_config.operation, this->m_renderBuffer.getAttachmentType(), GL_RENDERBUFFER, this->m_renderBuffer.getId());

		if (glCheckFramebufferStatus(this->m_config.operation) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
		}

		glBindFramebuffer(this->m_config.operation, 0);
	}

	void FrameBuffer::onDetach() { glDeleteFramebuffers(1, &this->m_id); }

	void FrameBuffer::bind() const {
		glBindFramebuffer(this->m_config.operation, this->m_id);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer::unbind() const {
		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(this->m_config.operation, 0); 
	}

} // namespace Bolt
