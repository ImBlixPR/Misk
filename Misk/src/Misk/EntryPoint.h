#pragma once
#include "Core.h"
#include "Log.h"

#ifdef MK_PLATFORM_WINDOW

extern Misk::Applaction* Misk::CreateApplaction();

int main() {

	Misk::Log::init();

	MK_ERROR("hello");
	MK_CORE_CRITICAL("almaktar");
	MK_WARN("Imblix");
	MK_CORE_TRACE("Qais");

	auto app = Misk::CreateApplaction();
	app->run();
	delete app;


	return 0;
}

#endif // MK_PLATFORM_WINDOW

