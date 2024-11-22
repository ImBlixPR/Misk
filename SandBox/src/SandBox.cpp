#include <Misk.h>

#include "imgui.h"



class ExampleLayer : public Misk::Layer
{
public: 
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//MK_INFO("ExampleLayer::Update");

		if (Misk::Input::IsKeyPressed(MK_KEY_SPACE))
			MK_TRACE("space key is pressed!");
	}

	void OnImguiRender() override
	{
		static bool show_another_window = true;
		MK_ASSERT(Misk::ImguiLayer::GetImguiContext(), "sad!");
		ImGui::SetCurrentContext(Misk::ImguiLayer::GetImguiContext());

		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("My name is almakhtar and this my window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
	}

	void OnEvent(Misk::Event& e) override
	{
		//MK_TRACE("{0}", e.ToString());
	}
};

class DebugLayer : public Misk::Layer
{
public:
	DebugLayer() :
		Layer("Debug layer")
	{

	}

	void OnImguiRender() override
	{
		static bool show = true;
		ImGui::SetCurrentContext(Misk::ImguiLayer::GetImguiContext());
		if (show)
		{
			ImGui::Begin("Hello ImBlix");
			ImGui::Text("Finial I understand it now :) ");
			if (ImGui::Button("Close Me"))
				show = false;
			ImGui::End();
		}

	}
};



class SandBox : public Misk::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new DebugLayer());
	}

	~SandBox()
	{

	}
};

Misk::Application* Misk::CreateApplication()
{
	return new SandBox();
}