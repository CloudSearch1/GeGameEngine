#include "GeAnalytics/Hardware/CPUInfo.h"

float GeAnalytics::Hardware::CPUInfo::CalculateCPULoad()
{
	FILETIME idleTime, kernelTime, userTime;
	return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -100.0f;
}

float GeAnalytics::Hardware::CPUInfo::CalculateCPULoad(uint64_t p_idleTicks, uint64_t p_totalTicks)
{
	uint64_t totalTicksSinceLastTime = p_totalTicks - m_cpuPreviousTotalTicks;
	uint64_t idleTicksSinceLastTime = p_idleTicks - m_cpuPreviousIdleTicks;

	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

	m_cpuPreviousTotalTicks = p_totalTicks;
	m_cpuPreviousIdleTicks = p_idleTicks;

	return ret * 100.0f;
}

uint64_t GeAnalytics::Hardware::CPUInfo::FileTimeToInt64(const FILETIME& ft)
{
	return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}
