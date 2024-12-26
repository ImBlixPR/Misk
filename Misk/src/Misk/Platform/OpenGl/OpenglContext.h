#pragma once

#include "Misk/Render/Context.h"
#include "Misk/Window.h"
struct GLFWwindow;

namespace Misk
{

	class OpenglContext : public Context
	{
	public:
		OpenglContext(GLFWwindow* handleWindow);

		void Init() override;
		void mouseDispaly(GLFWwindow* myWindow, bool mouseOn = false);
		void SwapBuffer() override;

	private:
		GLFWwindow* m_HandleWindow;
	};
}