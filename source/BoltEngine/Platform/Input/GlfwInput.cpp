#include "../../Core/Input/KeyboardManager.hpp"

KeyAction KeyboardManager::isKeyPressed(const int &keycode) const {
    auto* window = OpenGlWindow::instance()->getCurentContext();

    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS ? KeyAction::KEY_PRESS : KeyAction::KEY_RELEASE;
}

