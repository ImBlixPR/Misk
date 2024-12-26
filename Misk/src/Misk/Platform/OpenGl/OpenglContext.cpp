#include "mkpch.h"
#include "OpenglContext.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>

Misk::OpenglContext::OpenglContext(GLFWwindow* handleWindow)
	: m_HandleWindow(handleWindow)
{

}

void Misk::OpenglContext::Init()
{
	glfwMakeContextCurrent(m_HandleWindow);
	

}

void Misk::OpenglContext::mouseDispaly(GLFWwindow* myWindow, bool mouseOn)
{

	if (mouseOn)
		glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



void Misk::OpenglContext::SwapBuffer()
{
	glfwSwapBuffers(m_HandleWindow);
}

