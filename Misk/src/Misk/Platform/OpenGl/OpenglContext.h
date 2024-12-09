#pragma once

#include "Misk/Render/Context.h"

struct GLFWwindow;

namespace Misk
{

	class OpenglContext : public Context
	{
	public:
		OpenglContext(GLFWwindow* handleWindow);

		void Init() override;
		void SwapBuffer() override;

	private:
		GLFWwindow* m_HandleWindow;
	};
}