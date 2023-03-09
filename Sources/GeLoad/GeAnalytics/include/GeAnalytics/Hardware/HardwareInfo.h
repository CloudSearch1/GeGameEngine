#pragma once

#include <chrono>


#include "GeAnalytics/Hardware/HardwareReport.h"
#include "GeAnalytics/Hardware/CPUInfo.h"
#include "GeAnalytics/Hardware/GPUInfo.h"
#include "GeAnalytics/Hardware/RAMInfo.h"

namespace GeAnalytics::Hardware
{
	class HardwareInfo final
	{
	public:
		HardwareInfo(double p_timeInterval = 1.0);

		HardwareReport GenerateReport();

		void Tick();

	private:
		void Update();

		double m_timeInterval;
		double m_timer;

		std::chrono::steady_clock::time_point	m_previousTime;
		std::chrono::steady_clock::time_point	m_currentTime;
		std::chrono::duration<double>			m_elapsedTime;

		float m_cpuUsage;
		float m_gpuUsage;
		
		CPUInfo m_cpuInfo;
		GPUInfo m_gpuInfo;
		RAMInfo m_ramInfo;
	};
}
