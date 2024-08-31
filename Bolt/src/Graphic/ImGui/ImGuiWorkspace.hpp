#pragma once

#include <Core/Layer.hpp>

namespace Bolt {

	class ImGuiDockSpace final : public Layer {
	private:
		bool m_open = true;
		
	public:
		ImGuiDockSpace(const std::string& name = "DockSpace");

		virtual ~ImGuiDockSpace() override;

		virtual void onEvent(const Event& e) override;

		virtual void onRender() override;
	};

}
