#pragma once

#include "../Core/Utils.hpp"
#include "../Core/Window.hpp"
#include "../Core/Log.hpp"

#include <mutex>
#include <string>

#include "../../dependencies/glad/include/glad/glad.h"
#include "../../dependencies/glfw/include/GLFW/glfw3.h"

namespace Bolt {
	class GlfwWindow : public Window {
	private:
		inline static std::shared_ptr<GlfwWindow> s_pointer;
		inline static std::mutex s_mutex;

		GLFWwindow *m_context = nullptr;
		std::string m_windowTitle = "a";

		GlfwWindow() :
			m_windowTitle("Bolt Engine") {
			this->setPosition({0, 0});
			this->setSize({1600, 900});
			BT_WARN_CORE("You should implement this like a layer so you can create multiple windows.");
		}

	public:
		GlfwWindow(GlfwWindow &other) = delete;

		void operator=(const GlfwWindow &other) = delete;

		inline static std::shared_ptr<GlfwWindow> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				std::shared_ptr<GlfwWindow> copy(new GlfwWindow());
				copy.swap(s_pointer);
			}

			return s_pointer;
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
