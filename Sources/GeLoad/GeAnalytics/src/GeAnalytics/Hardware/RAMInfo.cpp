#include "GeAnalytics/Hardware/RAMInfo.h"

void GeAnalytics::Hardware::RAMInfo::Update()
{
	m_statex.dwLength = sizeof(m_statex);
	GlobalMemoryStatusEx(&m_statex);
}

float GeAnalytics::Hardware::RAMInfo::GetUsedRAM()
{
	return GetMaxRAM() - m_statex.ullAvailPhys / 1048576.0f;
}

float GeAnalytics::Hardware::RAMInfo::GetFreeRAM()
{
	return m_statex.ullAvailPhys / 1048576.0f;
}

float GeAnalytics::Hardware::RAMInfo::GetMaxRAM()
{
	return m_statex.ullTotalPhys / 1048576.0f;
}
