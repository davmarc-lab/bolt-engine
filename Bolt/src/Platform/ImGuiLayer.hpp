#pragma once

#include "GlfwWindow.hpp"
#include "../Core/Layer.hpp"

#include "../Core/Window.hpp"

namespace Bolt {
	class ImGuiLayer final : public Layer {
	private:
		Shared<GlfwWindow> m_window;
	public:
		ImGuiLayer(Shared<GlfwWindow> w) : Layer("ImGui"), m_window(w) {}

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onEvent(const Event& e) override;

		virtual void begin() override;

		virtual void end() override;
	};
}
