#pragma once

#include "../Core/Utils.hpp"
#include "../Core/Window.hpp"
#include "../Core/Log.hpp"

#include <string>

#include "../../dependencies/glad/include/glad/glad.h"
#include "../../dependencies/glfw/include/GLFW/glfw3.h"

namespace Bolt {
	
	class GlfwWindow final : public Window {
	private:
		GLFWwindow* m_context = nullptr;
		std::string m_windowTitle = "a";

	public:
		GlfwWindow() :
			m_windowTitle("Bolt Engine") {
			this->setPosition({0, 0});
			this->setSize({1600, 900});
			/* BT_WARN_CORE("You should implement this like a layer so you can create multiple windows."); */
		}
		
		b8 shouldWindowClose() const;

		virtual void setVsync(const b8 &enabled) override;

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onEvent(const Event &e) override;

		virtual void onUpdate() override;

		virtual void onRender() override;

	};
}
