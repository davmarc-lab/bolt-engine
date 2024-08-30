#pragma once

#include <Core/Structs.hpp>

#include <Core/Event.h>

namespace Bolt {
	class Window {
		protected:
			WinPos m_position;
			WinSize m_size;

			bool m_vsync = false;

			void* m_window;

		public:
			Window() {}

			virtual ~Window() {}

			inline const uint16_t& getWidth() const { return this->m_size.width; }

			inline const uint16_t& getHeight() const { return this->m_size.height; }

			inline void setSize(const WinSize& size) { this->m_size = size; }

			inline const WinPos& getPosition() const { return this->m_position; }

			inline void setPosition(const WinPos& position) { this->m_position = position; }

			inline virtual void setVsync(const bool& vsync) { this->m_vsync = vsync; }

			inline const bool& isVerticalSyncEnable() const { return this->m_vsync; }

			inline void* getCurrentWindow() const { return this->m_window; }

			virtual void onUpdate() {}

			virtual void onRender() {}

			virtual void onEvent(const Event& e) {}
	};
}
