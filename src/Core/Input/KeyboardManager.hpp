#pragma once

#include "../../includes/KeyboardEnums.hpp"

#include "../Graphics/Window/OpenGlWindow.hpp"

#include <memory>
#include <mutex>

class KeyboardManager {
  private:
    inline static std::shared_ptr<KeyboardManager> pointer = nullptr;
    inline static std::mutex mutex;
    KeyPress m_keyPressed;

    KeyboardManager() {}

  public:
    KeyboardManager(KeyboardManager &other) = delete;

    void operator=(const KeyboardManager &other) = delete;

    inline static std::shared_ptr<KeyboardManager> instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr) {
            std::shared_ptr<KeyboardManager> copy(new KeyboardManager());
            copy.swap(pointer);
        }

        return pointer;
    }

    inline void pollKeyPressed() {
        auto window = OpenGlWindow::instance()->getCurentContext();

        this->m_keyPressed = KeyPress{KEY_UNKNOWN, 0, KEY_NO_ACTION, KEY_MOD_NONE};

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            this->m_keyPressed = KeyPress{KEY_W, glfwGetKeyScancode(GLFW_KEY_W), KEY_PRESS, KEY_MOD_NONE};
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            this->m_keyPressed = KeyPress{KEY_A, glfwGetKeyScancode(GLFW_KEY_A), KEY_PRESS, KEY_MOD_NONE};
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            this->m_keyPressed = KeyPress{KEY_S, glfwGetKeyScancode(GLFW_KEY_S), KEY_PRESS, KEY_MOD_NONE};
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            this->m_keyPressed = KeyPress{KEY_D, glfwGetKeyScancode(GLFW_KEY_D), KEY_PRESS, KEY_MOD_NONE};
        }
    }

    inline KeyPress getLastKey() { return this->m_keyPressed; }

    // inline std::optional<KeyPress> getNext() {
    //     if (this->mIterator >= this->mKeyQueue.end())
    //         return std::nullopt;
    //     return std::optional<KeyPress>{*(this->mIterator++)};
    // }
};
