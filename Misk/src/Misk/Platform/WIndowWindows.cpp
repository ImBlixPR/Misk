#include "mkpch.h"
#include "WindowWindows.h"



#include <glad/glad.h>



namespace Misk {

	static bool IsGLFWInitialize = false;

	static void GLFWErrorCallBack(int error_code, const char* description)
	{
		MK_CORE_ERROR("GLFW Error ({0}) : {1}", error_code, description);
	}
	Window *Window::Create(const WindowProps& props)
	{
		//To be implemented by platform 
		//if we want to add another platform we have to implement this fuction in superclass cpp 
		return new WindowWindows(props);
	}


	WindowWindows::WindowWindows(const WindowProps& props)
	{
		m_YChange = 0;
		m_XChange = 0;
		Init(props);
	}

	WindowWindows::~WindowWindows()
	{
		Shutdown();
	}

	void WindowWindows::OnUpdate()
	{
		glfwPollEvents();
		context->SwapBuffer();
	}

	void WindowWindows::MouseOn(bool mouseOn)
	{
		context->mouseDispaly(m_Window, mouseOn);
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

	float WindowWindows::GetYChange()
	{
		GLfloat theChange = m_YChange;
		m_YChange = 0.0f;
		return theChange;
	}

	float WindowWindows::GetXChange()
	{
		GLfloat theChange = m_XChange;
		m_XChange = 0.0f;
		return theChange;
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
			glfwSetErrorCallback(GLFWErrorCallBack);
			IsGLFWInitialize = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		context = new OpenglContext(m_Window);

		context->Init();
		context->mouseDispaly(m_Window, false);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		//Wiondow resize event call back
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallBack(event);

			});

		//Window close event call back
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallBack(event);
			});


		//Window Key event call back
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);


				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallBack(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallBack(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallBack(event);
						break;
					}
				}

			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoin)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(codepoin);
				data.EventCallBack(event);
			});

		//Window mouse scroll event call back
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.EventCallBack(event);
			});

		//Window mouse button event call back
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallBack(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallBack(event);
						break;
					}
				}
			});


		//Window mouse move event call back
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallBack(event);
			});

		
	}

	void WindowWindows::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		delete context;
	}

}