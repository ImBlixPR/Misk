#pragma once
#include "Core.h"

#include "Misk/Event/Event.h"
#include "Misk/Core/Timestep.h"

namespace Misk {

	class   Layer
	{
	public:
		Layer(std::string debugName = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDettach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImguiRender() {}
		virtual std::string GetName() { return m_DebugName; }


	protected:
		std::string m_DebugName;

	};
}

