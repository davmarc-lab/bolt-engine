#pragma once

#include "../../../includes/OpenGl.hpp"

#include "../Buffers/VAO.hpp"

#include <memory>
#include <mutex>

class GlRender {
  private:
    inline static std::shared_ptr<GlRender> pointer = nullptr;
    inline static std::mutex mutex;

    GlRender() {}

  public:
    GlRender(GlRender &other) = delete;

    void operator=(const GlRender &other) = delete;

    inline static std::shared_ptr<GlRender> instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr) {
            std::shared_ptr<GlRender> copy(new GlRender());
            copy.swap(pointer);
        }

        return pointer;
    }

    inline void init() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    inline void setPolygonMode(const GLenum &face = GL_FRONT_AND_BACK, const GLenum &mode = GL_FILL) { glPolygonMode(face, mode); }

    inline void setLineWidth(const float &width = 1.f) { glLineWidth(width); }

    inline void drawLinesArrays(const VAO &vao, const GLsizei &count, const GLint &first = 0) {
        vao.bind();
        glDrawArrays(GL_LINES, first, count);
    }

    inline void drawLinesElements(const VAO &vao, const GLsizei &count) {
        vao.bind();
        glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, nullptr);
    }

    inline void drawTrianglesArrays(const VAO &vao, const GLsizei &count, const GLint &first = 0) {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, first, count);
    }

    inline void drawTrianglesElements(const VAO &vao, const GLsizei &count) {
        vao.bind();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
};
