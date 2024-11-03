#pragma once

#include "Core.h"
#include "Window.h"
#include "mkpch.h"
#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"

struct vec3 {
	float x;
	float y;
	float z;
};


namespace Misk {

	class MISK_API Appliction {
	public:
		Appliction();
		virtual ~Appliction();
		void run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnMouseMove(MouseMovedEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		vec3 color = { 1.0f, 0.0f, 1.0f };
	};


	//to be define in CLIENT
	Appliction* CreateAppliction();
}
