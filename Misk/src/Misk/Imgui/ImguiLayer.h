#pragma once



#include "Misk/Layer.h"
#include "Misk/Platform/OpenGl/imgui_impl_opengl3.h"
#include "imgui.h"

#include "Misk/Event/KeyEvent.h"
#include "Misk/Event/MouseEvent.h"
#include "Misk/Event/ApplicationEvent.h "


namespace Misk {


	class MISK_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		void OnAttach();
		void OnDettach();
		void OnUpdate();
		void OnEvent(Event& e);

	private: 
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


        ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode = 1);


	private:
		float m_Time = 0.0f;
		ImVec4 clear_color;
	};



}
