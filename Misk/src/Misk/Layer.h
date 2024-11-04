#pragma once
#include "Core.h"
#include "Misk/Event/Event.h"

namespace Misk {

	class MISK_API Layer
	{
	public:
		Layer(std::string debugName = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDettach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

	protected:
		std::string m_DebugName;

	};
}

