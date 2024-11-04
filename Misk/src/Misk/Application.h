#pragma once

#include "Misk/Core.h"
#include "Misk/Window.h"
#include "Misk/Event/ApplicationEvent.h"
#include "Misk/Event/MouseEvent.h"
#include "Misk/LayerStack.h"
#include <memory>



namespace Misk {

	class MISK_API Application {
	public:
		Application();
		virtual ~Application();
		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		

		LayerStack m_LayerStack;
	};


	//to be define in CLIENT
	Application* CreateApplication();
}
