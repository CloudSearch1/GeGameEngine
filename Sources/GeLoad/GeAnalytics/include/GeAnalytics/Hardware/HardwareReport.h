#pragma once



namespace GeAnalytics::Hardware
{
	struct HardwareReport final
	{
		float CPULoad;

		float GPULoad;

		float RAMUsed;

		float RAMFree;

		float RAMMax;
	};
}
