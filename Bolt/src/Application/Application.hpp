#pragma once

#include "../Core/Core.hpp"

namespace Bolt {
	/*
	 * Basic entry point to use the engine.
	 */
	class BOLT_API Application {
	public:
		Application() {}

		/*
		 * Starts the aplication, and enters in the loop.
		 */
		void run();

		~Application() {}
	};

    /*
    * This method need to be defined in a class extending Application.
    *
    * @returns an application with custom behavior.
    */
	Application *createApplication();
} // namespace Bolt
