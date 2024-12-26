#pragma once

#include "Misk/Window.h"

#include <GLFW/glfw3.h>

//event header
#include "Misk/Event/ApplicationEvent.h"
#include "Misk/Event/MouseEvent.h"
#include "Misk/Event/KeyEvent.h"
#include "Misk/Platform/OpenGl/OpenglContext.h"




namespace Misk
{

	class WindowWindows : public Window
	{
	public:
		WindowWindows(const WindowProps& props);
		virtual ~WindowWindows();

		void OnUpdate() override;
		void MouseOn(bool mouseOn) override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		//window attribute 
		virtual void SetEventCallBack(const EventCallBackFn& callBack) override { m_Data.EventCallBack = callBack; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		//getter and setter
		inline float GetLastX() { return m_LastX; }
		inline float GetLastY() { return m_LastY; }
		float GetYChange();
		float GetXChange();
		inline void SetLastX(float lastX) { m_LastX = lastX; }
		inline void SetLastY(float lastY) { m_LastY = lastY; }
		inline void SetYChange(float YChange) { m_YChange = YChange; }
		inline void SetXChange(float XChange) { m_XChange = XChange; }

		//my things temp
		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private :
		GLFWwindow* m_Window;

		float m_LastX;
		float m_LastY;
		float m_XChange;
		float m_YChange;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallBackFn EventCallBack;
		};

		OpenglContext* context;

		WindowData m_Data;
	};
}
