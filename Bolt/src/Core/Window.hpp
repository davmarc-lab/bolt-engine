#pragma once

#include <Core/Utils.hpp>
#include <Core/Structs.hpp>

#include <Core/Event.hpp>

#include <Core/Layer.hpp>

namespace Bolt {
	class Window : public Layer {
	protected:
		WinPos m_position;
		WinSize m_size;

		b8 m_vsync = false;

		void* m_window;

	public:
		Window() : Layer("Glfw Window") {}

		virtual ~Window() {}

		inline const u16& getWidth() const { return this->m_size.width; }

		inline const u16& getHeight() const { return this->m_size.height; }

		inline void setSize(const WinSize& size) { this->m_size = size; }

		inline const WinPos& getPosition() const { return this->m_position; }

		inline void setPosition(const WinPos& position) { this->m_position = position; }

		inline virtual void setVsync(const bool& vsync) { this->m_vsync = vsync; }

		inline const b8& isVerticalSyncEnable() const { return this->m_vsync; }

		inline void* getCurrentWindow() const { return this->m_window; }

		// --- Layer ---
		virtual void onAttach() override {}

		virtual void onDetach() override {}

		virtual void onEvent(const Event& e) override {}

		virtual void onUpdate() override {}

		virtual void onRender() override {}
	};
}
