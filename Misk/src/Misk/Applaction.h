#pragma once

#include "Core.h"



namespace Misk {

	class MISK_API Applaction {
	public:
		Applaction();
		virtual ~Applaction();
		void run();
	};


	//to be define in CLIENT
	Applaction* CreateApplaction();
}
