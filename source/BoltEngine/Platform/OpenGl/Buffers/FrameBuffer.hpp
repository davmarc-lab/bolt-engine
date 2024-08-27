#pragma once

#include "../../../includes/Const.hpp"

#include "../../../includes/OpenGl.hpp"

#include <memory>

struct FrameBuffer {
  private:
    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_tex;

    float m_width;
    float m_height;

  public:
    FrameBuffer() : FrameBuffer(IG_FRAME_WIDTH, IG_FRAME_HEIGHT) {}

    FrameBuffer(const float &width, const float &height) : m_width(width), m_height(height) {}

    bool init();

    void rescaleRenderBuffer(const float &width, const float &height);

    GLuint bind() const;

    void unbind() const;

    inline void setWidth(const float &width) { this->m_width = width; }

    inline float getWidth() const { return this->m_width; }

    inline void setHeight(const float &height) { this->m_height = height; }

    inline float getHeight() const { return this->m_height; }

    inline GLuint getTextureId() const { return this->m_tex; }

    ~FrameBuffer() {
        glDeleteFramebuffers(1, &this->m_fbo);
        glDeleteTextures(1, &this->m_tex);
        glDeleteRenderbuffers(1, &this->m_rbo);
    }
};

inline std::unique_ptr<FrameBuffer> mainFrameBuffer = std::make_unique<FrameBuffer>(IG_FRAME_WIDTH, IG_FRAME_HEIGHT);
