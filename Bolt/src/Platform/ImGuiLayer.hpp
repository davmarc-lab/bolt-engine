#pragma once

#include <imgui.h>
#include <Core/Layer.hpp>

namespace Bolt {
	class ImGuiLayer final : public Layer {
	public:
		ImGuiLayer() : Layer("ImGui") {}

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onEvent(const Event& e) override;

		void begin();

		void end();
	};
}
