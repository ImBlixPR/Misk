#include "Applaction.h"
#include <iostream>

#include "Event/ApplicationEvent.h"
#include "Log.h"


namespace Misk {





	Applaction::Applaction()
	{
	}

	Applaction::~Applaction()
	{
	}

	void Applaction::run()
	{
		WindowResizeEvent e(1280, 720);
		MK_TRACE(e.ToString());

		while (true);
	}

}
