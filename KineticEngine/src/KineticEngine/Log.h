#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace KE {
	class KE_API Log {
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

// Core logging macros
#define KE_CORE_TRACE(...)	::KE::Log::getCoreLogger()->trace(__VA_ARGS__)
#define KE_CORE_INFO(...)	::KE::Log::getCoreLogger()->info(__VA_ARGS__)
#define KE_CORE_WARN(...)	::KE::Log::getCoreLogger()->warn(__VA_ARGS__)
#define KE_CORE_ERROR(...)	::KE::Log::getCoreLogger()->error(__VA_ARGS__)
#define KE_CORE_FATAL(...)	::KE::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define KE_TRACE(...)		::KE::Log::getClientLogger()->trace(__VA_ARGS__)
#define KE_INFO(...)		::KE::Log::getClientLogger()->info(__VA_ARGS__)
#define KE_WARN(...)		::KE::Log::getClientLogger()->warn(__VA_ARGS__)
#define KE_ERROR(...)		::KE::Log::getClientLogger()->error(__VA_ARGS__)
#define KE_FATAL(...)		::KE::Log::getClientLogger()->critical(__VA_ARGS__)