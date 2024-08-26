#pragma once

#include "../../includes/KeyboardEnums.hpp"

#include "../Graphics/Window/OpenGlWindow.hpp"

#include <memory>
#include <mutex>

#define NUM_KEYS 48

class KeyboardManager {
  private:
    inline static std::shared_ptr<KeyboardManager> pointer = nullptr;
    inline static std::mutex mutex;

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

    KeyAction isKeyPressed(const int &keycode) const;
};
