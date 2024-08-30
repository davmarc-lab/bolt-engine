#pragma once

#include <Core/Core.hpp>

namespace Bolt {

	class BOLT_API Application {
	public:
		Application() {}

		void run();

		~Application() {}
	};

	Application* createApplication();
}
