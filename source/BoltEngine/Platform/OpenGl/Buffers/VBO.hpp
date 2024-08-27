#pragma once

#include "../../../includes/OpenGl.hpp"

#include <utility>
#include <vector>

class VBO {
  private:
    GLuint m_id;

  public:
    VBO() = default;
    VBO(const VBO &other) = delete;
    VBO(VBO &&other) { *this = std::move(other); }
    ~VBO() {
        if (m_id)
            glDeleteBuffers(1, &m_id);
    }
    VBO &operator=(const VBO &other) = delete;
    VBO &operator=(VBO &&other) {
        if (this != &other) {
            if (m_id)
                glDeleteBuffers(1, &m_id);
            m_id = std::exchange(other.m_id, 0);
        }
        return *this;
    }

    /**
     * @brief Generates the buffer for the VBO.
     */
    inline void genBuffer() { glGenBuffers(1, &this->m_id); }

    /**
     * @brief Binds the VBO.
     */
    inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->m_id); }

    /**
     * @brief Sets up the data for the buffer.
     * @param vertices A pointer to an array of floats to use as data.
     * @param size The size in bytes of the data.
     * @param usage The usage type, default GL_STATIC_DRAW.
     */
    void setup(const GLfloat *vertices, const GLsizeiptr &size, const GLenum &usage = GL_STATIC_DRAW);

    /**
     * @brief Sets up the data for the buffer.
     * @tparam T Things stored *contiguously* in memory.
     * @param vertices A pointer to an array of Ts to use as data.
     * @param size The size in bytes of the data.
     * @param usage The usage type, default GL_STATIC_DRAW.
     */
    template <typename T> void setup(const T *vertices, const GLsizeiptr &size, const GLenum &usage = GL_STATIC_DRAW) {
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    }

    /**
     * @brief Sets up the data for the buffer.
     * @tparam T You might want this to some numeric, vector, etc type for good result,
     * @param vertices A std::vector of something to use as data.
     * @param usage The usage type, default GL_STATIC_DRAW.
     */
    template <typename T> void setup(const std::vector<T> &vertices, const GLenum &usage = GL_STATIC_DRAW) {
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), usage);
    }

    /**
     * @brief Sets up the data for the buffer avoiding the cost of reallocating
     *  the data store.
     * @tparam T Things stored *contiguously* in memory.
     * @param vertices A pointer to an array of Ts to use as data.
     * @param size The size in bytes of the data.
     * @param offset The offset into the buffer object's data store where data
     *  replacement will begin, measured in bytes.
     */
    template <typename T> void setupSubData(const T *vertices, const GLsizeiptr &size, const GLintptr &offset = 0) {
        this->bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
    }

    /**
     * @brief Sets up the data for the buffer avoiding the cost of reallocating
     *  the data store.
     * @tparam T You might want this to some numeric, vector, etc type for good result,
     * @param vertices A std::vector of floats to use as data.
     * @param offset The offset into the buffer object's data store where data
     *  replacement will begin, measured in bytes.
     */
    template <typename T> void setupSubData(const std::vector<T> &vertices, const GLintptr &offset = 0) {
        this->bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * sizeof(T), vertices.data());
    }

    /**
     * @brief Unbinds the VBO.
     */
    void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
};
