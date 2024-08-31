#pragma once

#include <string>
#include <Core/Event.hpp>

namespace Bolt {
	class Layer {
	protected:
		std::string m_layerName;
		bool m_isFocused = false;

	public:
		Layer(std::string name);

		virtual ~Layer() = default;

		const bool& isFocused() const;

		virtual void onAttach() {}

		virtual void onDetach() {}

		virtual void onEvent(const Event& e) {}

		virtual void onUpdate() {}

		virtual void onRender() {}
	};
}
