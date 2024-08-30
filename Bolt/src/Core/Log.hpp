#pragma once

#include <Core/Core.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Bolt {

	class BOLT_API Log {
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	public:
		Log() {}

		~Log() {}

		static void init();

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }

		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
	};
}

#define BT_INFO_CORE(...) ::Bolt::Log::getCoreLogger()->info(__VA_ARGS__)
#define BT_DEBUG_CORE(...) ::Bolt::Log::getCoreLogger()->debug(__VA_ARGS__)
#define BT_WARN_CORE(...) ::Bolt::Log::getCoreLogger()->warn(__VA_ARGS__)
#define BT_ERROR_CORE(...) ::Bolt::Log::getCoreLogger()->error(__VA_ARGS__)
#define BT_CRITICAL_CORE(...) ::Bolt::Log::getCoreLogger()->critical(__VA_ARGS__)

#define BT_INFO(...) ::Bolt::Log::getClientLogger()->info(__VA_ARGS__)
#define BT_DEBUG(...) ::Bolt::Log::getClientLogger()->debug(__VA_ARGS__)
#define BT_WARN(...) ::Bolt::Log::getClientLogger()->warn(__VA_ARGS__)
#define BT_ERROR(...) ::Bolt::Log::getClientLogger()->error(__VA_ARGS__)
#define BT_CRITICAL(...) ::Bolt::Log::getClientLogger()->critical(__VA_ARGS__)