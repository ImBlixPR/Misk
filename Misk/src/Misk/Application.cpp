#include "mkpch.h"

#include "Application.h"

#include <glad/glad.h>





namespace Misk {




	Application* Application::m_Instanc = nullptr;

	Application::Application()
	{

		MK_CORE_ASSERT(!m_Instanc, "there is already an insttance of the application")
		m_Instanc = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(MK_BIND_EVENT_FN(Application::OnEvent));

	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_Running)
		{
			//Set clear color 
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			// Clear both color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MK_BIND_EVENT_FN(Application::OnWindowClose));
		//MK_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
