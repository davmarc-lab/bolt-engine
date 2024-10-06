#pragma once

#include "../Core/Utils.hpp"
#include "../Core/Structs.hpp"

#include "../Core/Event.hpp"

#include "../Core/Layer.hpp"

#include "../Core/Scene.hpp"

namespace bolt {
	class Window : public Layer {
	protected:
		WinPos m_position;
		WinSize m_size;

		b8 m_vsync = false;

		void* m_window = nullptr;
		std::string m_windowTitle = "Glfw Window";

	public:
		Window() : Window("Bolt Engine", {0, 0}, {1600, 900}) {}

        Window(std::string title, u16 xpos, u16 ypos, u16 width, u16 height) : Window(title, {xpos, ypos}, {width, height}) {}

        Window(std::string title, WinPos position, WinSize size) : m_windowTitle(title.c_str()), Layer("Glfw Window") {
			this->setPosition(position);
			this->setSize(size);
            scene::perspectiveProjection = perspective(45.0f, static_cast<f32>(this->m_size.width) / this->m_size.height, 0.1f, 100.f);;
            scene::orthoProjection = ortho(0.f, static_cast<f32>(this->m_size.width), 0.f, static_cast<f32>(this->m_size.height));
        }

		virtual ~Window() = default;

		inline const u16& getWidth() const { return this->m_size.width; }

		inline const u16& getHeight() const { return this->m_size.height; }

		inline void setSize(const WinSize& size) { this->m_size = size; }

		inline const WinPos& getPosition() const { return this->m_position; }

		inline void setPosition(const WinPos& position) { this->m_position = position; }

		virtual b8 shouldWindowClose() const;

		virtual void setVsync(const bool& vsync);

		inline const b8& isVerticalSyncEnable() const { return this->m_vsync; }

		inline void* getCurrentWindow() const { return this->m_window; }

		// --- Layer ---
		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onEvent(const Event& e) override;

		virtual void onUpdate() override;

		virtual void onRender() override;

		virtual void end() override;
	};
}
