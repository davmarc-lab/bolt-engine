#pragma once

#include "../Core/Scene.hpp"

namespace bolt {

	struct ApplicationSetting {
		scene::SceneType type;
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

		inline static void setProjectionMatrix(const mat4& proj) { s_projection = proj; }

		~Application() = default;
	};
} // namespace bolt
