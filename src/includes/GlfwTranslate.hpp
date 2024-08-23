#pragma once

#include "KeyboardEnums.hpp"
#include "OpenGl.hpp"

class Translator {
  private:
    inline static Key getKey(int key) {
        switch (key) {
        case GLFW_KEY_Q:
            return Key::KEY_Q;
        case GLFW_KEY_W:
            return Key::KEY_W;
        case GLFW_KEY_A:
            return Key::KEY_A;
        case GLFW_KEY_S:
            return Key::KEY_S;
        case GLFW_KEY_D:
            return Key::KEY_D;
        default:
            return Key::KEY_UNKNOWN;
        }
    }

    inline static KeyAction getAction(int action) {
        switch (action) {
        case GLFW_PRESS:
            return KeyAction::KEY_PRESS;
        case GLFW_RELEASE:
            return KeyAction::KEY_RELEASE;
        case GLFW_REPEAT:
            return KeyAction::KEY_REPEAT;
        default:
            return KeyAction::KEY_NO_ACTION;
        }
    }

    inline static KeyMod getMod(int mod) {
        switch (mod) {
        case GLFW_MOD_SUPER:
            return KeyMod::KEY_MOD_SUPER;
        case GLFW_MOD_SHIFT:
            return KeyMod::KEY_MOD_SHIFT;
        case GLFW_MOD_CONTROL:
            return KeyMod::KEY_MOD_CONTROL;
        case GLFW_MOD_ALT:
            return KeyMod::KEY_MOD_ALT;
        case GLFW_MOD_NUM_LOCK:
            return KeyMod::KEY_MOD_NUM_LOCK;
        case GLFW_MOD_CAPS_LOCK:
            return KeyMod::KEY_MOD_CAPS_LOCK;
        default:
            return KeyMod::KEY_MOD_NONE;
        }
    }

  public:
    inline static KeyPress translateGLFWKey(int key, int scancode, int action, int mod) {
        return KeyPress{getKey(key), scancode, getAction(action), getMod(mod)};
    }
};
