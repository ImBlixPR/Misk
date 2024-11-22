#include "mkpch.h"
#include "ImguiLayer.h"
#include "Misk/Application.h"
#include "Misk/Platform/WindowWindows.h"
#include "Misk/Core.h"
#include "Misk/Platform/OpenGl/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Misk/Platform/OpenGl/imgui_impl_glfw.h"



namespace Misk {

    ImGuiContext* ImguiLayer::m_ctx = nullptr;

	ImguiLayer::ImguiLayer()
		: Layer("Imgui Layer")
	{


	}

	ImguiLayer::~ImguiLayer()
	{
        
	}

	void ImguiLayer::OnAttach()
	{
        IMGUI_CHECKVERSION();
        m_ctx = ImGui::CreateContext();
        MK_CORE_ASSERT(ImGui::GetCurrentContext(), "Imgui context uninitalize!")
            //ImGui::SetCurrentContext(ctx);
            ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        //// Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        Application& app = Application::Get();

        auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        // Setup Platform/Renderer backends
        ImGui_ImplOpenGL3_Init("#version 410");

        MK_CORE_INFO("w: {0}, h: {1}", app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	}

	void ImguiLayer::OnDettach()
	{
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
	}

    void ImguiLayer::OnImguiRender()
    {
        //MK_CORE_ASSERT(false, "Imgui context uninitalize!")
        static bool show_demo_window = true;
        static bool show_another_window = true;
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    void ImguiLayer::Begin()
    {
        MK_CORE_ASSERT(ImGui::GetCurrentContext(), "Imgui context uninitalize!")
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImguiLayer::End()
    {

        MK_CORE_ASSERT(ImGui::GetCurrentContext(), "Imgui context uninitalize!")
        ImGuiIO& io = ImGui::GetIO();
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }




}
