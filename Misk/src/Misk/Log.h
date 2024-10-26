#pragma once



#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Core.h"


namespace Misk {

	class MISK_API Log
	{
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_clientLogger; }



	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};

}

//log core macro
#define MK_CORE_ERROR(...)  ::Misk::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MK_CORE_TRACE(...)  ::Misk::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MK_CORE_WARN(...)   ::Misk::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MK_CORE_INFO(...)   ::Misk::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MK_CORE_CRITICAL(...)  ::Misk::Log::GetCoreLogger()->critical(__VA_ARGS__)

//log client macro
#define MK_ERROR(...)  ::Misk::Log::GetClientLogger()->error(__VA_ARGS__)
#define MK_TRACE(...)  ::Misk::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MK_WARN(...)   ::Misk::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MK_INFO(...)   ::Misk::Log::GetClientLogger()->info(__VA_ARGS__)
#define MK_CRITICAL(...)  ::Misk::Log::GetClientLogger()->critical(__VA_ARGS__)

