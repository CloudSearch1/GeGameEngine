#pragma once

#include <string>
#include <chrono>


#include "GeAnalytics/Profiling/Profiler.h"
#include "GeAnalytics/Profiling/ProfilerSpy.h"


#define PROFILER_SPY(name)\
		std::unique_ptr<GeAnalytics::Profiling::ProfilerSpy> __profiler_spy__ = \
		GeAnalytics::Profiling::Profiler::IsEnabled() ? std::make_unique<GeAnalytics::Profiling::ProfilerSpy>(name) : nullptr

namespace GeAnalytics::Profiling
{

	struct ProfilerSpy final
	{

		ProfilerSpy(const std::string& p_name);

		~ProfilerSpy();

		const	std::string								name;
		const	std::chrono::steady_clock::time_point	start;
				std::chrono::steady_clock::time_point	end;
	};
}
