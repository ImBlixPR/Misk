#include "mkpch.h"

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include "Misk/Input.h"
#include "Misk/KeyCode.h"
#include "Misk/Core/Timestep.h"



namespace Misk {




	Application* Application::m_Instanc = nullptr;

	Application::Application()
	{

		MK_CORE_ASSERT(!m_Instanc, "there is already an insttance of the application")
		m_Instanc = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(MK_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);
		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);

	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		glEnable(GL_DEPTH_TEST); // Add this in your setup if depth is not needed.

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastTime;
			m_LastTime = time;

			OnMouseChange();
			if (Input::IsKeyPressed(MK_KEY_ESCAPE))
				m_Running = false;
			//Set clear color 
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			// Clear both color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}

			
			m_ImguiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImguiRender();
			}
			m_ImguiLayer->End();
			


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


	float Application::GetYChange()
	{
		float theChange = m_MouseProp.yChange;
		m_MouseProp.yChange = 0.0f;
		return theChange;
	}

	float Application::GetXChange()
	{
		float theChange = m_MouseProp.xChange;
		m_MouseProp.xChange = 0.0f;
		return theChange;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnMouseChange()
	{
		auto window = static_cast<GLFWwindow*>(this->GetWindow().GetNativeWindow());
		auto [x, y] = Input::GetMousePosition();
		if (m_MouseProp.firstMove)
		{
			m_MouseProp.lastX = x;
			m_MouseProp.lastY = y;
			m_MouseProp.firstMove = false;
		}

		m_MouseProp.xChange = x - m_MouseProp.lastX;
		m_MouseProp.yChange = m_MouseProp.lastY - y;

		m_MouseProp.lastX = x;
		m_MouseProp.lastY = y;
	}

}
