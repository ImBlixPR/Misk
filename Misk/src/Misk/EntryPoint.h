#pragma once
#include "Core.h"
#include "mkpch.h"


#ifdef MK_PLATFORM_WINDOWS

extern Misk::Appliction* Misk::CreateAppliction();

int main() {

	Misk::Log::init();

	MK_ERROR("hello");
	MK_CORE_ERROR("hello world!");
	MK_CORE_CRITICAL("almaktar");
	MK_WARN("Imblix");

	auto app = Misk::CreateAppliction();
	app->run();
	delete app;


	return 0;
}

#endif // MK_PLATFORM_WINDOW

