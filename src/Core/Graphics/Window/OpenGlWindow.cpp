#include "OpenGlWindow.hpp"

#include "../../../includes/Const.hpp"

#include "../../Input/KeyboardManager.hpp"

#include "IGPanel/IGFrameBuffer.hpp"
#include "IGPanel/IGLeftPanel.hpp"

#include <iostream>

void glfwErrorCallback(int code, const char *description) {
    if (code != GLFW_NO_ERROR) {
        std::cout << "--- ERROR ---\n";
        std::cout << "Code: " << code << "\n"
                  << "Info: " << description << "\n";
        std::cout << "--- ----- ---\n";
    }
}

void glfwFramebufferSizeCallback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

void glfwCloseCallback(GLFWwindow *window) {}

void glfwKeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mod) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mod);
}

void OpenGlWindow::init() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Bolt Engine", NULL, NULL);

    // defines error callback
    glfwSetErrorCallback(glfwErrorCallback);

    if (this->m_window == NULL) {
        // Error
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(this->m_window);
#ifndef _WIN32
    glfwSetWindowPos(this->m_window, 5, 10);
#else
    glfwMaximizeWindow(this->m_window);
#endif // !_WIN32

    // focusing the created window and set a callback funciton for updating render when resizing window
    // checks if glad library has been loaded correctly
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        exit(-2);
    }

    // defines other callbacks
    glfwSetFramebufferSizeCallback(this->m_window, glfwFramebufferSizeCallback);
    // glfwSetWindowCloseCallback(this->mWindow, glfwCloseCallback);
    glfwSetKeyCallback(this->m_window, glfwKeyboardCallback);

    glfwSetInputMode(this->m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(this->m_window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    // Enable V-Sync
    glfwSwapInterval(1);

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->m_imGuiIo = &ImGui::GetIO();
    m_imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    m_imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    m_imGuiIo->ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking Feature
    // mImGuiIo->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable MultiViewport Feature

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();

    // init all imgui windows
    ImGuiLeftPanel::instance()->init();
    ImGuiFramePanel::instance()->init();

    // main framebuffer
    mainFrameBuffer->init();
}

void OpenGlWindow::pollEvents() {
    glfwPollEvents();
}

void OpenGlWindow::render() {
    mainFrameBuffer->bind();
    glClearColor(0.f, 0.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mainFrameBuffer->unbind();
}

void OpenGlWindow::renderImGui() {
    // ImGui render

    ImGuiLeftPanel::instance()->render();
    ImGuiFramePanel::instance()->render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OpenGlWindow::destroy() {
    mainFrameBuffer.reset();

    // clear imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // clear opengl
    glfwTerminate();
}
