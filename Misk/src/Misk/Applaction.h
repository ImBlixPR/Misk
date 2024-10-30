#pragma once

#include "Core.h"
#include "Window.h"
#include "mkpch.h"


namespace Misk {

	class MISK_API Applaction {
	public:
		Applaction();
		virtual ~Applaction();
		void run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};


	//to be define in CLIENT
	Applaction* CreateApplaction();
}
