#pragma once

#include "../../includes/KeyboardEnums.hpp"

#include <iostream>
#include <memory>
#include <mutex>

class KeyboardEvent {

  private:
    inline static std::shared_ptr<KeyboardEvent> pointer = nullptr;
    inline static std::mutex mutex;

    KeyboardEvent() {}

  public:
    KeyboardEvent(KeyboardEvent &other) = delete;

    void operator=(const KeyboardEvent &other) = delete;

    inline static std::shared_ptr<KeyboardEvent> instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr) {
            std::shared_ptr<KeyboardEvent> copy(new KeyboardEvent());
            copy.swap(pointer);
        }

        return pointer;
    }

    inline void handle(const KeyPress &key) {
        switch (key.action) {
        case KeyAction::KEY_PRESS:
            switch (key.key) {
            case Key::KEY_W:
                std::cout << "W pressed" << std::endl;
                break;
            case Key::KEY_S:
                std::cout << "S pressed" << std::endl;
                break;
            case Key::KEY_A:
                std::cout << "A pressed" << std::endl;
                break;
            case Key::KEY_D:
                std::cout << "D pressed" << std::endl;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
};
