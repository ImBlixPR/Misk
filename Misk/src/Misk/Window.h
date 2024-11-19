#pragma once

#include "mkpch.h"

#include "Event/Event.h"
#include "Misk/Input.h"

namespace Misk {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string title = "Misk Engine", unsigned int width = 1280 , unsigned int height = 720 )
			: Title(title), Width(width), Height(height)
		{

		}
	};


	class MISK_API Window {
	public:
		
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		//Getter function
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Setter function
		virtual void SetEventCallBack(const EventCallBackFn& callBack) = 0;
		virtual void SetVSync(bool enabled) = 0;

		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};
}






