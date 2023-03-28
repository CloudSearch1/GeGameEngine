#pragma once

#include <unordered_map>
#include <chrono>
#include <mutex>


#include "GeAnalytics/Profiling/ProfilerReport.h"

namespace GeAnalytics::Profiling
{
	struct ProfilerSpy;

	class Profiler final
	{
	public:
		Profiler();

		ProfilerReport GenerateReport();

		void ClearHistory();

		void Update(float p_deltaTime);

		static void Save(ProfilerSpy& p_spy);

		static bool IsEnabled();

		static void ToggleEnable();

		static void Enable();

		static void Disable();

	private:
		std::chrono::steady_clock::time_point m_lastTime;

		static bool __ENABLED;

		static std::mutex									__SAVE_MUTEX;
		static std::unordered_map<std::string, double>		__ELPASED_HISTORY;
		static std::unordered_map<std::string, uint64_t>	__CALLS_COUNTER;
		static std::vector<std::thread::id>					__WORKING_THREADS;
		static uint32_t										__ELAPSED_FRAMES;
	};
}
