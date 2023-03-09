#include "GeAnalytics/Profiling/ProfilerSpy.h"
#include "GeAnalytics/Profiling/Profiler.h"

GeAnalytics::Profiling::ProfilerSpy::ProfilerSpy(const std::string & p_name) :
	name(p_name),
	start(std::chrono::steady_clock::now())
{

}

GeAnalytics::Profiling::ProfilerSpy::~ProfilerSpy()
{
	end = std::chrono::steady_clock::now();
	GeAnalytics::Profiling::Profiler::Save(*this);
}
