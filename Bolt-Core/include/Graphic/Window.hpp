#pragma once

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

		void *m_window = nullptr;
		std::string m_windowTitle = "Glfw Window";

	public:
		Window() :
			Window("Bolt Engine", {0, 0}, {1600, 900}) {}

		Window(std::string title, const u16 xpos, const u16 ypos, const u16 width, const u16 height) :
			Window(std::move(title), {xpos, ypos}, {width, height}) {}

		Window(const ApplicationSetting &settings) :
			Window(settings.name, settings.position, settings.dimension) {
			this->m_vsync = settings.baseWindowProperties.vsync;
			this->m_clearColor = settings.baseWindowProperties.backgroundColor;
		}

		Window(std::string title, const Pair<u16> position, const Pair<u16> size) :
			Layer("Glfw Window"), m_windowTitle(std::move(title)) {
			this->m_position = position;
			this->m_size = size;
			
			switch (Application::getSceneType()) {
				case scene::SceneType::SCENE_2D:
					scene::updateOrtho(0.f, this->m_size.x, 0.f, this->m_size.y);
					break;
				case scene::SceneType::SCENE_3D:
					scene::updatePerspective(45.0f, static_cast<f32>(this->m_size.x) / this->m_size.y, 0.1f, 100.f);
					break;
			}
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

		// --- Layer ---
		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onEvent(const Event &e) override;

		virtual void onUpdate() override;

		virtual void onRender() override;

		virtual void end() override;
	};
} // namespace bolt
