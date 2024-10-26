#include "mkpch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Misk {

	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;
	
	void Log::init()
	{
		//set the pattern of log message
		spdlog::set_pattern("%^[%T] %n: %v%$");

		//setup logger for the core (engine)
		s_coreLogger = spdlog::stdout_color_mt("MISK");
		s_coreLogger->set_level(spdlog::level::trace);

		//setup logger for the appliction
		s_clientLogger = spdlog::stdout_color_mt("APP");
		s_clientLogger->set_level(spdlog::level::trace);
		

	}



}
