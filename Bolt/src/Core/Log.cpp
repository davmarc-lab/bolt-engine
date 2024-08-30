#include "Log.hpp"

namespace Bolt {
	
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		s_coreLogger = spdlog::stdout_color_mt("Bolt");
		BT_INFO_CORE("Logger created");
		s_clientLogger = spdlog::stdout_color_mt("App");
		BT_INFO("Logger created");
	}

}