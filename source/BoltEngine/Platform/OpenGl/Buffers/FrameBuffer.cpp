#include "FrameBuffer.hpp"

bool FrameBuffer::init() {
    glGenFramebuffers(1, &this->m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_fbo);

    glGenTextures(1, &this->m_tex);
    glBindTexture(GL_TEXTURE_2D, this->m_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_tex, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &this->m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, this->m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->m_width, this->m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void FrameBuffer::rescaleRenderBuffer(const float &width, const float &height) {
    this->m_width = width;
    this->m_height = height;

    glBindTexture(GL_TEXTURE_2D, this->m_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_tex, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, this->m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->m_width, this->m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_rbo);
}

GLuint FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_fbo);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return this->m_fbo;
}

void FrameBuffer::unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
