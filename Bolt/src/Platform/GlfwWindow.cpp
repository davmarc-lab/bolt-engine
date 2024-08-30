#include <Platform/GlfwWindow.hpp>

#include <Core/Log.hpp>

namespace Bolt {

    static void glfwErrorCallback(int code, const char *description) {
        BT_ERROR_CORE("GLFW error ({0} -> {1})", code, description);
    }

    static void glfwResizeCallback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        if (width < 0 || height < 0) {
            BT_WARN_CORE("Tried to assign negative window size.");
        }
        // Cannot use GlfwWindow::instance() inside this function.
        // -- BECAUSE YOU ARE IN THE CONSTRUCTOR OMG --
        BT_INFO_CORE("Window resized: w={0}, h={1}", width, height);
    }

    void GlfwWindow::init() {
        BT_INFO_CORE("Is Better to run GlfwWindow::init() out of the constructor.");
        // Init GLFW window
        BT_INFO_CORE("Initializing window called \"{0}\"", this->m_windowTitle);
        glfwInit();

        // Error callback function must use the logger
        glfwSetErrorCallback(glfwErrorCallback);

        BT_INFO_CORE("Creating Window \"{0}\"", this->m_windowTitle);
        
#ifdef BT_DEBUG
        BT_INFO_CORE("Debug activated");
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

        // Creating window
        this->m_context = glfwCreateWindow(this->getWidth(), this->getHeight(), this->m_windowTitle.c_str(), NULL, NULL);
        if (this->m_context == NULL) {
            BT_ERROR_CORE("Failed to create GLFW window.");
            BT_INFO_CORE("To be replaced with event.");
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(this->m_context);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            BT_ERROR_CORE("Failed to initialize GLAD.");
            glfwTerminate();
            BT_INFO_CORE("To be replaced with event.");
            exit(EXIT_FAILURE);
        }

        // Enabling vsync
        this->setVsync(this->isVerticalSyncEnable());

        // Callbacks time
        glfwSetFramebufferSizeCallback(this->m_context, glfwResizeCallback);

        // Enable some parameters
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

        glfwMaximizeWindow(this->m_context);
        {
            int width, height;
            glfwGetWindowSize(this->m_context, &width, &height);
            if (width >= 0 && height >= 0) {
                this->setSize({static_cast<uint16_t>(width), static_cast<uint16_t>(height)});
            } else {
                BT_WARN_CORE("Tried to assign negative window size.");
            }
        }
        
        BT_INFO_CORE("The renderer should do these things");
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        this->m_window = this->m_context;
    }

    void GlfwWindow::setVsync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
            BT_INFO_CORE("VSync enabled for Window \"{0}\"", this->m_windowTitle);
        } else {
            glfwSwapInterval(0);
            BT_INFO_CORE("VSync disabled for Window \"{0}\"", this->m_windowTitle);
        }
    }

    void GlfwWindow::onUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(this->m_context);
    }

    void GlfwWindow::onRender() {
        glClearColor(0.f, 0.f, 1.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }


    bool GlfwWindow::shouldWindowClose() const {
        return glfwWindowShouldClose(this->m_context);
    }

    void GlfwWindow::destroy() const {
        glfwDestroyWindow(this->m_context);
        glfwTerminate();
    }
}