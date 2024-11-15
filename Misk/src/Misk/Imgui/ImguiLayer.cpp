#include "mkpch.h"
#include "ImguiLayer.h"
#include "Misk/Application.h"
#include "Misk/Platform/WindowWindows.h"
#include "Misk/Core.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
//#include "Misk/Platform/OpenGl/imgui_impl_glfw.h"



namespace Misk {

	ImguiLayer::ImguiLayer()
		: Layer("Imgui Layer")
	{

	}

	ImguiLayer::~ImguiLayer()
	{
	}

	void ImguiLayer::OnAttach()
	{
	
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		//// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		
		
		// Setup Platform/Renderer backends
		ImGui_ImplOpenGL3_Init("#version 410");

		Application& app = Application::Get();
		MK_CORE_INFO("w: {0}, h: {1}", app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	}

	void ImguiLayer::OnDettach()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
	
		ImGui::DestroyContext();
	}

	void ImguiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1 / 60.0f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

    void ImguiLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyTypedEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<KeyPressedEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<WindowResizeEvent>(MK_BIND_EVENT_FN(ImguiLayer::OnWindowResizeEvent));

    }

	bool ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.GetMouseButton(), true);
		return false;
	}

	bool ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetMouseButton(), false);
		return false;
	}

	bool ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());
		return false;
	}

	bool ImguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return false;
	}

    bool ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        // Update the key event for the pressed key
        io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode()), true);
        io.AddKeyEvent(ImGuiMod_Ctrl, (GLFW_KEY_LEFT_CONTROL == e.GetKeyCode() || GLFW_KEY_RIGHT_CONTROL == e.GetKeyCode()));
        io.AddKeyEvent(ImGuiMod_Shift, (GLFW_KEY_LEFT_SHIFT == e.GetKeyCode() || GLFW_KEY_RIGHT_SHIFT == e.GetKeyCode()));
        io.AddKeyEvent(ImGuiMod_Alt, (GLFW_KEY_LEFT_ALT == e.GetKeyCode() || GLFW_KEY_RIGHT_ALT == e.GetKeyCode()));
        io.AddKeyEvent(ImGuiMod_Super, (GLFW_KEY_LEFT_SUPER == e.GetKeyCode() || GLFW_KEY_RIGHT_SUPER == e.GetKeyCode()));


        return false; // Continue with other event handling as needed
    }


	bool ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode()), false);
		return false;
	}

	bool ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

	bool ImguiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
        
		ImGuiIO& io = ImGui::GetIO();
        if(e.GetKeyCode() > 0 && e.GetKeyCode() < 0x10000)
            io.AddInputCharacter(e.GetKeyCode());
        io.AddKeyEvent(ImGuiMod_Ctrl, (GLFW_KEY_LEFT_CONTROL == e.GetKeyCode() || GLFW_KEY_RIGHT_CONTROL == e.GetKeyCode()));
        io.AddKeyEvent(ImGuiMod_Shift, (GLFW_KEY_LEFT_SHIFT == e.GetKeyCode() || GLFW_KEY_RIGHT_SHIFT == e.GetKeyCode()));
        io.AddKeyEvent(ImGuiMod_Alt, (GLFW_KEY_LEFT_ALT == e.GetKeyCode() || GLFW_KEY_RIGHT_ALT == e.GetKeyCode()));
        io.AddKeyEvent(ImGuiMod_Super, (GLFW_KEY_LEFT_SUPER == e.GetKeyCode() || GLFW_KEY_RIGHT_SUPER == e.GetKeyCode()));
		return false;
	}

	ImGuiKey ImguiLayer::ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode)
	{
        IM_UNUSED(scancode);
        switch (keycode)
        {
        case GLFW_KEY_TAB: return ImGuiKey_Tab;
        case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
        case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
        case GLFW_KEY_UP: return ImGuiKey_UpArrow;
        case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
        case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
        case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
        case GLFW_KEY_HOME: return ImGuiKey_Home;
        case GLFW_KEY_END: return ImGuiKey_End;
        case GLFW_KEY_INSERT: return ImGuiKey_Insert;
        case GLFW_KEY_DELETE: return ImGuiKey_Delete;
        case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
        case GLFW_KEY_SPACE: return ImGuiKey_Space;
        case GLFW_KEY_ENTER: return ImGuiKey_Enter;
        case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
        case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
        case GLFW_KEY_COMMA: return ImGuiKey_Comma;
        case GLFW_KEY_MINUS: return ImGuiKey_Minus;
        case GLFW_KEY_PERIOD: return ImGuiKey_Period;
        case GLFW_KEY_SLASH: return ImGuiKey_Slash;
        case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
        case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
        case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
        case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
        case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
        case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
        case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
        case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
        case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
        case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
        case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
        case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
        case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
        case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
        case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
        case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
        case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
        case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
        case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
        case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
        case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
        case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
        case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
        case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
        case GLFW_KEY_MENU: return ImGuiKey_Menu;
        case GLFW_KEY_0: return ImGuiKey_0;
        case GLFW_KEY_1: return ImGuiKey_1;
        case GLFW_KEY_2: return ImGuiKey_2;
        case GLFW_KEY_3: return ImGuiKey_3;
        case GLFW_KEY_4: return ImGuiKey_4;
        case GLFW_KEY_5: return ImGuiKey_5;
        case GLFW_KEY_6: return ImGuiKey_6;
        case GLFW_KEY_7: return ImGuiKey_7;
        case GLFW_KEY_8: return ImGuiKey_8;
        case GLFW_KEY_9: return ImGuiKey_9;
        case GLFW_KEY_A: return ImGuiKey_A;
        case GLFW_KEY_B: return ImGuiKey_B;
        case GLFW_KEY_C: return ImGuiKey_C;
        case GLFW_KEY_D: return ImGuiKey_D;
        case GLFW_KEY_E: return ImGuiKey_E;
        case GLFW_KEY_F: return ImGuiKey_F;
        case GLFW_KEY_G: return ImGuiKey_G;
        case GLFW_KEY_H: return ImGuiKey_H;
        case GLFW_KEY_I: return ImGuiKey_I;
        case GLFW_KEY_J: return ImGuiKey_J;
        case GLFW_KEY_K: return ImGuiKey_K;
        case GLFW_KEY_L: return ImGuiKey_L;
        case GLFW_KEY_M: return ImGuiKey_M;
        case GLFW_KEY_N: return ImGuiKey_N;
        case GLFW_KEY_O: return ImGuiKey_O;
        case GLFW_KEY_P: return ImGuiKey_P;
        case GLFW_KEY_Q: return ImGuiKey_Q;
        case GLFW_KEY_R: return ImGuiKey_R;
        case GLFW_KEY_S: return ImGuiKey_S;
        case GLFW_KEY_T: return ImGuiKey_T;
        case GLFW_KEY_U: return ImGuiKey_U;
        case GLFW_KEY_V: return ImGuiKey_V;
        case GLFW_KEY_W: return ImGuiKey_W;
        case GLFW_KEY_X: return ImGuiKey_X;
        case GLFW_KEY_Y: return ImGuiKey_Y;
        case GLFW_KEY_Z: return ImGuiKey_Z;
        case GLFW_KEY_F1: return ImGuiKey_F1;
        case GLFW_KEY_F2: return ImGuiKey_F2;
        case GLFW_KEY_F3: return ImGuiKey_F3;
        case GLFW_KEY_F4: return ImGuiKey_F4;
        case GLFW_KEY_F5: return ImGuiKey_F5;
        case GLFW_KEY_F6: return ImGuiKey_F6;
        case GLFW_KEY_F7: return ImGuiKey_F7;
        case GLFW_KEY_F8: return ImGuiKey_F8;
        case GLFW_KEY_F9: return ImGuiKey_F9;
        case GLFW_KEY_F10: return ImGuiKey_F10;
        case GLFW_KEY_F11: return ImGuiKey_F11;
        case GLFW_KEY_F12: return ImGuiKey_F12;
        case GLFW_KEY_F13: return ImGuiKey_F13;
        case GLFW_KEY_F14: return ImGuiKey_F14;
        case GLFW_KEY_F15: return ImGuiKey_F15;
        case GLFW_KEY_F16: return ImGuiKey_F16;
        case GLFW_KEY_F17: return ImGuiKey_F17;
        case GLFW_KEY_F18: return ImGuiKey_F18;
        case GLFW_KEY_F19: return ImGuiKey_F19;
        case GLFW_KEY_F20: return ImGuiKey_F20;
        case GLFW_KEY_F21: return ImGuiKey_F21;
        case GLFW_KEY_F22: return ImGuiKey_F22;
        case GLFW_KEY_F23: return ImGuiKey_F23;
        case GLFW_KEY_F24: return ImGuiKey_F24;
        default: return ImGuiKey_None;
        }
	}



}
