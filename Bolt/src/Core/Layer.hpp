#pragma once

#include <Core/Event.hpp>

namespace Bolt {
	class Layer {
		private:
			bool m_isFocused = false;

		public:
			Layer() = default;

			virtual ~Layer() = default;

			const bool& isFocused() const;

			virtual void onAttach() = 0;

			virtual void onDetach() = 0;

			virtual void onUpdate() = 0;

			virtual void onRender() = 0;

			virtual void onEvent(const Event& e) = 0;
	};
}
