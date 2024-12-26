#pragma once


namespace Misk {


	struct Timestep {

		Timestep(float time = 0.0f)
			:m_Time(time)
		{

		}

		operator float() { return m_Time; }

		float GetTimeSec() { return m_Time; }
		float GetTimeMilSec() { return m_Time * 1000.0f; }


	private:
		float m_Time;
	};
}