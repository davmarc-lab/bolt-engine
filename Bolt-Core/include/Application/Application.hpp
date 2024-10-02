#pragma once

#include "../Core/Core.hpp"

namespace bolt {
	/*
	 * Basic entry point to use the engine.
	 */
	class Application {
    private:
        inline static bool s_enableimGui = false;
	public:
		Application() {}

		/*
		 * Starts the aplication, and enters in the loop.
		 */
		void run();

        inline static void enableImGui() { s_enableimGui = true; }

        inline static bool isImGuiEnabled() { return s_enableimGui; }

		~Application() {}
	};

    /*
    * This method need to be defined in a class extending Application.
    *
    * @returns an application with custom behavior.
    */
	Application *createApplication();
} // namespace Bolt
