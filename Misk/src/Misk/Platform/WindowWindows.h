#pragma once

#include "Misk/Window.h"

#include <GLFW/glfw3.h>

//event header
#include "Misk/Event/ApplicationEvent.h"
#include "Misk/Event/MouseEvent.h"
#include "Misk/Event/KeyEvent.h"





namespace Misk
{

	class WindowWindows : public Window
	{
	public:
		WindowWindows(const WindowProps& props);
		virtual ~WindowWindows();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//window attribute 
		virtual void SetEventCallBack(const EventCallBackFn& callBack) override { m_Data.EventCallBack = callBack; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		//my things temp
		virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private :
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallBackFn EventCallBack;
		};

		WindowData m_Data;
	};
}
