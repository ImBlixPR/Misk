#pragma once



#include "Misk/Layer.h"
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

		virtual void OnAttach() override;
		virtual void OnDettach() override;
		void OnImguiRender() override;
		inline static ImGuiContext* GetImguiContext() { return m_ctx; }

		void Begin();
		void End();



	private:
		float m_Time = 0.0f;
		ImVec4 clear_color;
		static ImGuiContext* m_ctx;
	};



}
