#pragma once

#include <Windows.h>
#include <psapi.h>

namespace GeAnalytics::Hardware
{
	class RAMInfo final
	{
	public:
		void Update();

		float GetUsedRAM();

		float GetFreeRAM();

		float GetMaxRAM();

	private:
		MEMORYSTATUSEX m_statex;
	};
}
