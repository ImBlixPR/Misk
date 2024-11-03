#include "mkpch.h"

#include "Appliction.h"

#include <GLFW/glfw3.h>





namespace Misk {


#define BIND_EVENT_FN(x) std::bind(&Appliction::x, this, std::placeholders::_1)


	Appliction::Appliction()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
	}

	Appliction::~Appliction()
	{
	}

	void Appliction::run()
	{
		while (m_Running)
		{
			//Set clear color 
			glClearColor(color.x, color.y, color.z, 1.0f);
			// Clear both color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer
			
			m_Window->OnUpdate();
		}
	}

	void Appliction::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMove));
		MK_CORE_TRACE("{0}", e.ToString());
	}

	bool Appliction::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Appliction::OnMouseMove(MouseMovedEvent& e)
	{
		color.x = e.GetX() / 1280;
		color.y = e.GetY() / 720;
		return true;
	}

}
