#pragma once

#include "Misk/Core.h"
#include "Misk/Window.h"
#include "Misk/Event/ApplicationEvent.h"
#include "Misk/Event/MouseEvent.h"
#include "Misk/LayerStack.h"
#include "Misk/Imgui/ImguiLayer.h"
#include <memory>



namespace Misk {

	class   Application {
	public:
		Application();
		virtual ~Application();
		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *m_Instanc; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImguiLayer* m_ImguiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* m_Instanc;
	};


	//to be define in CLIENT
	Application* CreateApplication();
}
