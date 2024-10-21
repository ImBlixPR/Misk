#pragma once
#include "Core.h"

#ifdef MK_PLATFORM_WINDOW

extern Misk::Applaction* Misk::CreateApplaction();

int main() {

	auto app = Misk::CreateApplaction();
	app->run();
	delete app;


	return 0;
}

#endif // MK_PLATFORM_WINDOW

