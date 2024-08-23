#pragma once

#include "../../../includes/OpenGl.hpp"
#include "../../../includes/ImGui.hpp"

#include <memory>
#include <mutex>

class OpenGlWindow {
  private:
    inline static std::shared_ptr<OpenGlWindow> pointer = nullptr;
    inline static std::mutex mutex;

    GLFWwindow *m_window;
    GLFWwindow *m_backupContext;
    ImGuiIO *m_imGuiIo;

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

    inline void prepareImGuiRender() {
        // Prepare ImGui Render
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void render();

    void renderImGui();

    inline GLFWwindow *getCurentContext() { return this->m_window; }

    inline void makeGlfwContextBackup() {
        if (this->m_imGuiIo->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            this->m_backupContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(this->m_backupContext);
        }
    }

    void pollEvents();

    inline void swapBuffers() { glfwSwapBuffers(this->m_window); }

    inline void closeWindow() { glfwSetWindowShouldClose(this->m_window, GL_TRUE); }

    void destroy();

    void init();
};
