#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <Core/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Bolt {
    class GlfwWindow : public Window {
    private:
        inline static std::shared_ptr<GlfwWindow> s_pointer;
        inline static std::mutex s_mutex;
        
        GLFWwindow* m_context = nullptr;
        std::string m_windowTitle = "a";

        void init();
        
        GlfwWindow() : m_windowTitle("Bolt Engine") {
            this->setPosition({0, 0});
            this->setSize({1600, 900});
            this->init();
        }
        
    public:
        GlfwWindow(GlfwWindow &other) = delete;

        void operator=(const GlfwWindow &other) = delete;
        
        inline static std::shared_ptr<GlfwWindow> instance() {
            if (s_pointer == nullptr) {
                std::shared_ptr<GlfwWindow> copy(new GlfwWindow());
                copy.swap(s_pointer);
            }

            return s_pointer;
        }

        virtual void setVsync(bool enabled) override;

        virtual void onUpdate() override;

        virtual void onRender() override;

        bool shouldWindowClose() const;

        void destroy() const;
    };
}
