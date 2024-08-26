#pragma once

#include "../../../includes/OpenGl.hpp"

#include <utility>
#include <vector>

class EBO {
  private:
    GLuint m_id;

  public:
    EBO() = default;
    EBO(const EBO &other) = delete;
    EBO(EBO &&other) { *this = std::move(other); }
    ~EBO() {
        if (m_id)
            glDeleteBuffers(1, &m_id);
    }
    EBO &operator=(const EBO &other) = delete;
    EBO &operator=(EBO &&other) {
        if (this != &other) {
            if (m_id)
                glDeleteBuffers(1, &m_id);
            m_id = std::exchange(other.m_id, 0);
        }
        return *this;
    }

    inline void genBuffer() { glGenBuffers(1, &this->m_id); }

    inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id); }

    /**
     * @brief Sets up the data for the buffer.
     * @param indices A pointer to an array of floats to use as data.
     * @param size The size in bytes of the data.
     * @param usage The usage type, default GL_STATIC_DRAW.
     */
    void setup(const GLfloat *indices, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW);

    /**
     * @brief Sets up the data for the buffer.
     * @tparam T Things stored *contiguously* in memory.
     * @param indices A pointer to an array of Ts to use as data.
     * @param size The size in bytes of the data.
     * @param usage The usage type, default GL_STATIC_DRAW.
     */
    template <typename T> void setup(const T *indices, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW) {
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, size, indices, usage);
    }

    /**
     * @brief Sets up the data for the buffer.
     * @tparam T You might want this to some numeric, vector, etc type for good result,
     * @param indices A std::vector of something to use as data.
     * @param usage The usage type, default GL_STATIC_DRAW.
     */
    template <typename T> void setup(const std::vector<T> &indices, const GLenum& usage = GL_STATIC_DRAW) {
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(T), indices.data(), usage);
    }

    inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};
