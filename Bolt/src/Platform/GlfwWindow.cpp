#include <Platform/GlfwWindow.hpp>

#include <Core/Log.hpp>

#include <string>

namespace Bolt {

	#ifdef BT_ENABLE_DEBUG
	const char* getErrorSource(const GLenum& source) {
		switch (source) {
			case GL_DEBUG_SOURCE_API: return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
			case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
			case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
			case GL_DEBUG_SOURCE_APPLICATION: return "Application";
			default: return "Other";
		}
	}

	const char* getErrorType(const GLenum& type) {
		switch (type) {
			case GL_DEBUG_TYPE_ERROR: return "Error";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behaviour";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behaviour";
			case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
			case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
			case GL_DEBUG_TYPE_MARKER: return "Marker";
			case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
			case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
			default: return "Other";
		}
	}

	// TODO : Try to implement a macro for the string created (or use streams)
	void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam) {
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		// It should be fine using a temporary string to print debug information.
		{
			const auto msg = "GLFW Debug Output:\n" + std::string("Code (") + std::to_string(id) + "): " + message + "\n" + "Source: " + getErrorSource(source) + "\n" + "Type: " + getErrorType(type) + "\n" + "File: " + __FILE__ + " (" + std::to_string(__LINE__) + ")";

			switch (severity) {
				case GL_DEBUG_SEVERITY_LOW: BT_WARN_CORE(msg);
					break;
				case GL_DEBUG_SEVERITY_MEDIUM: BT_ERROR_CORE(msg);
					break;
				case GL_DEBUG_SEVERITY_HIGH: BT_CRITICAL_CORE(msg);
					break;
				default: BT_INFO_CORE(msg);
					break;
			}
		}
	}
	#endif

	static void glfwErrorCallback(int code, const char* description) { BT_ERROR_CORE("GLFW error ({0} -> {1})", code, description); }

	static void glfwResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);

		if (width < 0 || height < 0) { BT_WARN_CORE("Tried to assign negative window size."); }

		GlfwWindow::instance()->setSize({static_cast<uint16_t>(width), static_cast<uint16_t>(height)});
		BT_INFO_CORE("Window resized: w={0}, h={1}", width, height);
	}

	bool GlfwWindow::shouldWindowClose() const { return glfwWindowShouldClose(this->m_context); }
	
	void GlfwWindow::setVsync(const bool& enabled) {
		if (enabled) {
			glfwSwapInterval(1);
			BT_INFO_CORE("VSync enabled for Window \"{0}\"", this->m_windowTitle);
		}
		else {
			glfwSwapInterval(0);
			BT_INFO_CORE("VSync disabled for Window \"{0}\"", this->m_windowTitle);
		}
	}

	void GlfwWindow::onAttach() {
		// Init GLFW window
		BT_INFO_CORE("Initializing GLFW context");
		glfwInit();

		// Error callback function must use the logger
		glfwSetErrorCallback(glfwErrorCallback);

		BT_INFO_CORE("Creating Window \"{0}\"", this->m_windowTitle);

		#ifdef BT_ENABLE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		BT_INFO_CORE("Debug activated");
		#endif

		// Creating window
		this->m_context = glfwCreateWindow(this->getWidth(), this->getHeight(), this->m_windowTitle.c_str(), NULL, NULL);
		if (this->m_context == NULL) {
			BT_ERROR_CORE("Failed to create GLFW window.");
			BT_INFO_CORE("To be replaced with event.");
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(this->m_context);

		// Init glad loader
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			BT_ERROR_CORE("Failed to initialize GLAD.");
			glfwTerminate();
			BT_INFO_CORE("To be replaced with event.");
			exit(EXIT_FAILURE);
		}

		#ifdef BT_ENABLE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

		{
			int debugFlags;
			glGetIntegerv(GL_CONTEXT_FLAGS, &debugFlags);

			if (debugFlags & GL_CONTEXT_FLAG_DEBUG_BIT) {
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(glDebugOutput, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
				BT_INFO_CORE("GLFW Debugger Initialized.");
			}
		}
		#endif

		// Enabling vsync
		this->setVsync(this->isVerticalSyncEnable());

		// Callbacks time
		glfwSetFramebufferSizeCallback(this->m_context, glfwResizeCallback);

		// Enable some parameters
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		{
			int width, height;
			glfwGetWindowSize(this->m_context, &width, &height);
			if (width >= 0 && height >= 0) { this->setSize({static_cast<uint16_t>(width), static_cast<uint16_t>(height)}); }
			else { BT_WARN_CORE("Tried to assign negative window size."); }
		}

		BT_INFO_CORE("The renderer should do these things");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		this->m_window = this->m_context;
	}

	void GlfwWindow::onDetach() {
		glfwDestroyWindow(this->m_context);
	}
	
	void GlfwWindow::onEvent(const Event& e) {
		// BT_INFO_CORE("No Implementation of Event handling.");
	}


	void GlfwWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(this->m_context);
	}

	void GlfwWindow::onRender() {
		// Default clear operations.
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
