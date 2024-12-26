#include <Misk.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "game/Game.h"


Misk::Application* Misk::CreateApplication()
{
	return new Game();
}

int main() {

	Misk::Log::init();

	MK_ERROR("hello");
	MK_CORE_ERROR("hello world!");
	MK_CORE_CRITICAL("almaktar");
	MK_WARN("Imblix");

	auto app = Misk::CreateApplication();
	app->run();
	delete app;


	return 0;
}