#pragma once

#include "../Core/Scene.hpp"
#include "../Core/Structs.hpp"

namespace bolt {
	struct WindowProperties {
		b8 maximized = false;
		b8 vsync = false;
		vec4 backgroundColor = vec4(0.3f, 0.3f, 0.3f, 1.0f);
	};

	struct ApplicationSetting {
		scene::SceneType type;
		std::string name = "Bolt App";
		Pair<u16> dimension = {1600, 900};
		Pair<u16> position = {};
		WindowProperties baseWindowProperties;
	};

	/*
	 * Basic entry point to use the engine.
	 */
	class Application {
	private:
		inline static bool s_enableImGui = false;

		inline static ApplicationSetting s_settings{};

		inline static mat4 s_projection{};

	public:
		Application() :
			Application({scene::SceneType::SCENE_3D}) {}

		Application(const ApplicationSetting &settings) {
			s_settings = settings;
		}

		/*
		 * Starts the aplication, and enters in the loop.
		 */
		void run();

		inline static void enableImGui() { s_enableImGui = true; }

		inline static bool isImGuiEnabled() { return s_enableImGui; }

		inline static scene::SceneType getSceneType() { return s_settings.type; }

		inline static mat4 getProjectionMatrix() { return s_projection; }

		inline static void setProjectionMatrix(const mat4 &proj) {
			s_projection = proj;
		}

		~Application() = default;
	};
} // namespace bolt
