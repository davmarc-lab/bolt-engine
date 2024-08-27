#pragma once

#include "../../../includes/OpenGl.hpp"

#include "VBO.hpp"

#include <utility>

struct VAO {
  private:
    GLuint m_id;

  public:
    VAO() = default;
    VAO(const VAO &other) = delete;
    VAO(VAO &&other) { *this = std::move(other); }
    ~VAO() {
        if (m_id)
            glDeleteVertexArrays(1, &m_id);
    }
    VAO &operator=(const VAO &other) = delete;
    VAO &operator=(VAO &&other) {
        if (this != &other) {
            if (m_id)
                glDeleteVertexArrays(1, &m_id);
            m_id = std::exchange(other.m_id, 0);
        }
        return *this;
    }

    void bind() const { glBindVertexArray(this->m_id); }


    void linkAttrib(const VBO &vbo, const GLuint& layout, const GLuint& components, const GLenum& type, const GLsizei& stride, void *offset,
                    const GLboolean& normalize = GL_FALSE) const;

    void linkAttribFast(const GLuint& layout, const GLuint& components, const GLenum& type, const GLsizei& stride, void *offset, const GLboolean& normalize = GL_FALSE) const;

    void genVertexArray();

    void unbind() const { glBindVertexArray(0); }
};
