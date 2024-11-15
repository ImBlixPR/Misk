#include <Misk.h>


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
	}

	void OnEvent(Misk::Event& e) override
	{
		//MK_TRACE("{0}", e.ToString());
	}
};


class SandBox : public Misk::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Misk::ImguiLayer());
	}

	~SandBox()
	{

	}
};

Misk::Application* Misk::CreateApplication()
{
	return new SandBox();
}