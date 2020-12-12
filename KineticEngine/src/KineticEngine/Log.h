#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"

namespace KE {
	class KE_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

// Core logging macros
#define KE_CORE_TRACE(...)	::KE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KE_CORE_INFO(...)	::KE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KE_CORE_WARN(...)	::KE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KE_CORE_ERROR(...)	::KE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KE_CORE_FATAL(...)	::KE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define KE_TRACE(...)		::KE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KE_INFO(...)		::KE::Log::GetClientLogger()->info(__VA_ARGS__)
#define KE_WARN(...)		::KE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KE_ERROR(...)		::KE::Log::GetClientLogger()->error(__VA_ARGS__)
#define KE_FATAL(...)		::KE::Log::GetClientLogger()->critical(__VA_ARGS__)