#include "mkpch.h"

#include "Applaction.h"

#include <GLFW/glfw3.h>

#include "Event/ApplicationEvent.h"
#include "Log.h"


namespace Misk {





	Applaction::Applaction()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Applaction::~Applaction()
	{
	}

	void Applaction::run()
	{
		while (m_Running)
		{
			//Set clear color 
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			// Clear both color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer
			
			m_Window->OnUpdate();
		}
	}

}
