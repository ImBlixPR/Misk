#include "mkpch.h"
#include "WindowWindows.h"


namespace Misk {

	static bool IsGLFWInitialize = false;


	Window *Window::Create(const WindowProps& props)
	{
		//To be implemented by platform 
		//if we want to add another platform we have to implement this fuction in superclass cpp 
		return new WindowWindows(props);
	}


	WindowWindows::WindowWindows(const WindowProps& props)
	{
		Init(props);
	}

	WindowWindows::~WindowWindows()
	{
		Shutdown();
	}

	void WindowWindows::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowWindows::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowWindows::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowWindows::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MK_CORE_INFO("Creating Window {0} ({1} , {2})", m_Data.Title, m_Data.Width, m_Data.Height);


		if (!IsGLFWInitialize)
		{
			int succes = glfwInit();
			MK_CORE_ASSERT(succes, "Could not intialize GLFW");

			IsGLFWInitialize = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowWindows::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}