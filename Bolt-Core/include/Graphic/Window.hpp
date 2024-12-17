#pragma once

#include <functional>
#include "../Application/Application.hpp"
#include "../Core/Structs.hpp"
#include "../Core/Utils.hpp"

#include "../Core/Event.hpp"

#include "../Core/Layer.hpp"

namespace bolt {
	class Window : public Layer {
	protected:
		Pair<u16> m_position{};
		Pair<u16> m_size{};

		b8 m_vsync = false;
		vec4 m_clearColor = vec4(0, 0, 0, 1);

		ApplicationSetting m_settings{};

		void *m_window = nullptr;
		std::string m_windowTitle = "Glfw Window";
		u32 m_clearMask = 0;

		// callbacks
		std::function<void(void *, i32, i32, i32, i32)> m_keyCallback = nullptr;
		std::function<void(void *, i32, i32, i32)> m_mouseButtonCallback = nullptr;
		std::function<void(void *, f64, f64)> m_cursorPosCallback = nullptr;

		void updateUserPointer();

	public:
		Window(const ApplicationSetting &settings) :
			Layer("Glfw Window"), m_windowTitle(std::move(settings.name)) {
			this->m_position = settings.position;
			this->m_size = settings.dimension;
			this->m_vsync = settings.properties.vsync;
			this->m_clearColor = settings.properties.backgroundColor;

			this->m_settings = settings;

			scene::updateTextProj(0.f, this->m_size.x, 0.f, this->m_size.y);
			EventDispatcher::instance()->post(events::shader::ShaderProjectionChanged);
		}

		virtual ~Window() = default;

		inline const u16 &getWidth() const { return this->m_size.x; }

		inline const u16 &getHeight() const { return this->m_size.y; }

		inline void setSize(const Pair<u16> &size) { this->m_size = size; }

		inline const Pair<u16> &getPosition() const { return this->m_position; }

		inline void setPosition(const Pair<u16> &position) { this->m_position = position; }

		virtual b8 shouldWindowClose() const;

		virtual void setVsync(const bool &vsync);

		inline const b8 &isVerticalSyncEnable() const { return this->m_vsync; }

		inline void *getCurrentWindow() const { return this->m_window; }

		inline vec4 getClearColor() const { return this->m_clearColor; }

		inline void setClearColor(const vec4 &color) { this->m_clearColor = color; }

		void setKeyboardCallback(std::function<void(void *, i32, i32, i32, i32)> &&func);

		void execKeyboardCallback(void *context, i32 key, i32 code, i32 action, i32 mods);

		void setMouseButtonCallback(std::function<void(void *, i32, i32, i32)> &&func);

		void execMouseButtonCallback(void *context, i32 button, i32 action, i32 mods);

		void setCursorPosCallback(std::function<void(void *, f64, f64)> &&func);

		void execCursorPosCallback(void *context, f64 xpos, f64 ypos);

		// --- Layer ---
		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onEvent(const Event &e) override;

		virtual void onUpdate() override;

		virtual void onRender() override;

		virtual void begin() override;

		virtual void end() override;
	};
} // namespace bolt
