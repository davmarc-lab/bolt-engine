#pragma once

#include "../../../includes/OpenGl.hpp"

#include "../../../includes/Structs.hpp"

#include <memory>
#include <mutex>

class OpenGlWindow {
  private:
    inline static std::shared_ptr<OpenGlWindow> pointer = nullptr;
    inline static std::mutex mutex;

    GLFWwindow *m_window;

    WinSize m_size;

    OpenGlWindow() {}

  public:
    OpenGlWindow(OpenGlWindow &other) = delete;

    void operator=(const OpenGlWindow &other) = delete;

    inline static std::shared_ptr<OpenGlWindow> instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr) {
            std::shared_ptr<OpenGlWindow> copy(new OpenGlWindow());
            copy.swap(pointer);
        }

        return pointer;
    }

    inline bool shouldWindowClose() { return glfwWindowShouldClose(this->m_window); }

    void render();

    inline GLFWwindow *getCurentContext() { return this->m_window; }

    void pollEvents();

    inline void swapBuffers() { glfwSwapBuffers(this->m_window); }

    inline void closeWindow() { glfwSetWindowShouldClose(this->m_window, GL_TRUE); }

    void init();

    void destroy();

    inline float getWindowWidth() { return static_cast<float>(this->m_size.x); }

    inline float getWindowHeight() { return static_cast<float>(this->m_size.y); }

};
