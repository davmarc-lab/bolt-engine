﻿#include "../../include/Graphic/Window.hpp"

#include "../../include/Core/Utils.hpp"

#include "../../../Bolt-Graphics/include/glad/glad.h"
#include "../../../Bolt-Vendor/include/glfw/include/GLFW/glfw3.h"

#include "../../include/Graphic/Camera/Camera.hpp"

#include <string>

namespace bolt {

	struct Mouse {
		b8 firstMouse = true;
		f32 lastX = 0;
		f32 lastY = 0;
	} inline mouse;

	static u16 s_windowCount = 0;

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
	void glDebugOutput(const GLenum source,
		const GLenum type,
		const u32 id,
		const GLenum severity,
		const GLsizei length,
		const char* message,
		const void* userParam) {
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
			return;

		// It should be fine using a temporary string to print debug information.
		{
			const auto msg = "GLFW Debug Output:\n" + std::string("Code (") + std::to_string(id) + "): " + message + "\n" +
				"Source: " + getErrorSource(source) + "\n" + "Type: " + getErrorType(type) + "\n" + "File: " + __FILE__;

			switch (severity) {
			case GL_DEBUG_SEVERITY_LOW:
				/* BT_INFO_CORE(msg); */
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				/* BT_WARN_CORE(msg); */
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				/* BT_ERROR_CORE(msg); */
				break;
			default:
				/* BT_INFO_CORE(msg); */
				break;
			}
		}
	}
#endif

	static void glfwErrorCallback(i32 code, const char* description) { /* BT_ERROR_CORE("GLFW error ({0} -> {1})", code, description); */ }

	static void glfwResizeCallback(GLFWwindow* window, i32 width, i32 height) {
		glViewport(0, 0, width, height);

		scene::perspectiveProjection = perspective(radians(45.0f), static_cast<f32>(width) / height, 0.1f, 100.f);;
		scene::orthoProjection = ortho(0.f, static_cast<f32>(width), 0.f, static_cast<f32>(height));

		if (width < 0 || height < 0) { /* BT_WARN_CORE("Tried to assign negative window size."); */ }

		/* BT_INFO_CORE("Window resized: w={0}, h={1}", width, height); */
	}

	static void glfwKeyboardCallback(GLFWwindow* window, int key, int code, int action, int mod) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		// needs to be changed with WOLRD::AXIS
		if (key == GLFW_KEY_W && action != GLFW_RELEASE) {
			standardCamera.moveCamera(standardCamera.getCameraVelocity() * vec3(0, 0, 1));
		}
		if (key == GLFW_KEY_S && action != GLFW_RELEASE) {
			standardCamera.moveCamera(standardCamera.getCameraVelocity() * vec3(0, 0, -1));
		}

		if (key == GLFW_KEY_A && action != GLFW_RELEASE) {
			standardCamera.moveCamera(standardCamera.getCameraVelocity() * vec3(-1, 0, 0));
		}
		if (key == GLFW_KEY_D && action != GLFW_RELEASE) {
			standardCamera.moveCamera(standardCamera.getCameraVelocity() * vec3(1, 0, 0));
		}

		if (key == GLFW_KEY_SPACE && action != GLFW_RELEASE) {
			standardCamera.moveCamera(standardCamera.getCameraVelocity() * vec3(0, 1, 0));
		}
		if (key == GLFW_KEY_LEFT_SHIFT && action != GLFW_RELEASE) {
			standardCamera.moveCamera(standardCamera.getCameraVelocity() * vec3(0, -1, 0));
		}
	}

	static void glfwMouseMovementCallback(GLFWwindow* window, double x, double y) {
		if (mouse.firstMouse) {
			mouse.lastX = x;
			mouse.lastY = y;
			mouse.firstMouse = false;
		}

		standardCamera.processMouseMovement(x - mouse.lastX, y - mouse.lastY);

		mouse.lastX = x;
		mouse.lastY = y;
	}

	bool Window::shouldWindowClose() const { return glfwWindowShouldClose(static_cast<GLFWwindow*>(this->m_window)); }

	void Window::setVsync(const b8& enabled) {
		if (enabled) {
			glfwSwapInterval(1);
			/* BT_INFO_CORE("VSync enabled for Window \"{0}\"", this->m_windowTitle); */
		}
		else {
			glfwSwapInterval(0);
			/* BT_INFO_CORE("VSync disabled for Window \"{0}\"", this->m_windowTitle); */
		}
	}

	void Window::onAttach() {
		// Init GLFW window
		/* BT_INFO_CORE("Initializing GLFW context"); */
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// Error callback function must use the logger
		glfwSetErrorCallback(glfwErrorCallback);

		/* BT_INFO_CORE("Creating Window \"{0}\"", this->m_windowTitle); */

#ifdef BT_ENABLE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		/* BT_INFO_CORE("Debug activated"); */
#endif

// Creating window
		this->m_window = glfwCreateWindow(this->getWidth(), this->getHeight(), this->m_windowTitle.c_str(), NULL, NULL);
		if (this->m_window == NULL) {
			/* BT_ERROR_CORE("Failed to create GLFW window."); */
			/* BT_INFO_CORE("To be replaced with event."); */
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(static_cast<GLFWwindow*>(this->m_window));

		// Init glad loader
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			/* BT_ERROR_CORE("Failed to initialize GLAD."); */
			glfwTerminate();
			/* BT_INFO_CORE("To be replaced with event."); */
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
				/* BT_INFO_CORE("GLFW Debugger Initialized."); */
			}
		}
#endif

		// Enabling vsync
		this->setVsync(this->isVerticalSyncEnable());

		// Callbacks time
		glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(this->m_window), glfwResizeCallback);

		glfwSetKeyCallback(static_cast<GLFWwindow*>(this->m_window), glfwKeyboardCallback);

		// They are ready to work - BUG on Trello -
		//glfwSetInputMode(static_cast<GLFWwindow*>(this->m_window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//glfwSetCursorPosCallback(static_cast<GLFWwindow*>(this->m_window), glfwMouseMovementCallback);

		// Enable some parameters
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		{
			i32 width, height;
			glfwGetWindowSize(static_cast<GLFWwindow*>(this->m_window), &width, &height);
			if (width >= 0 && height >= 0) { this->setSize({ static_cast<u16>(width), static_cast<u16>(height) }); }
			else { /* BT_WARN_CORE("Tried to assign negative window size."); */ }
		}

		/* BT_INFO_CORE("The renderer should do these things"); */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		s_windowCount++;
	}

	void Window::onDetach() {
		glfwDestroyWindow(static_cast<GLFWwindow*>(this->m_window));
		s_windowCount--;

		if (s_windowCount == 0) {
		}
	}

	void Window::onEvent(const Event& e) {
		// BT_INFO_CORE("No Implementation of Event handling.");
	}

	void Window::onUpdate() {
		glfwPollEvents();
	}

	void Window::onRender() {
		// Default clear operations.
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::end() {
		glfwSwapBuffers(static_cast<GLFWwindow*>(this->m_window));
	}

} // namespace Bolt