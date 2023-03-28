#include <iostream>
#include <iomanip>
#include <map>
#include <string>

#include "GeAnalytics/Profiling/Profiler.h"
#include "GeAnalytics/Profiling/ProfilerSpy.h"

bool											GeAnalytics::Profiling::Profiler::__ENABLED;
std::mutex										GeAnalytics::Profiling::Profiler::__SAVE_MUTEX;
std::unordered_map<std::string, double>			GeAnalytics::Profiling::Profiler::__ELPASED_HISTORY;
std::unordered_map<std::string, uint64_t>		GeAnalytics::Profiling::Profiler::__CALLS_COUNTER;
std::vector<std::thread::id>					GeAnalytics::Profiling::Profiler::__WORKING_THREADS;
uint32_t										GeAnalytics::Profiling::Profiler::__ELAPSED_FRAMES;

GeAnalytics::Profiling::Profiler::Profiler()
{
	m_lastTime = std::chrono::high_resolution_clock::now();
	__ENABLED = false;
}

GeAnalytics::Profiling::ProfilerReport GeAnalytics::Profiling::Profiler::GenerateReport()
{
	ProfilerReport report;

	if (__ELAPSED_FRAMES == 0)
		return report;

	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - m_lastTime;

	report.workingThreads = static_cast<uint16_t>((__WORKING_THREADS.size() - 1) / __ELAPSED_FRAMES);
	report.elapsedFrames = __ELAPSED_FRAMES;
	report.elaspedTime = elapsed.count();

	std::multimap<double, std::string, std::greater<double>> sortedHistory;

	for (auto& data : __ELPASED_HISTORY)
		sortedHistory.insert(std::pair<double, std::string>(data.second, data.first));

	for (auto& data : sortedHistory)
		report.actions.push_back({ data.second, data.first, (data.first / elapsed.count()) * 100.0, __CALLS_COUNTER[data.second] });

	return report;
}

void GeAnalytics::Profiling::Profiler::ClearHistory()
{
	__ELPASED_HISTORY.clear();
	__CALLS_COUNTER.clear();
	__WORKING_THREADS.clear();
	__ELAPSED_FRAMES = 0;

	m_lastTime = std::chrono::high_resolution_clock::now();
}

void GeAnalytics::Profiling::Profiler::Update(float p_deltaTime)
{
	if (IsEnabled())
	{
		++__ELAPSED_FRAMES;
	}
}

void GeAnalytics::Profiling::Profiler::Save(GeAnalytics::Profiling::ProfilerSpy& p_spy)
{
	__SAVE_MUTEX.lock();

	if (std::find(__WORKING_THREADS.begin(), __WORKING_THREADS.end(), std::this_thread::get_id()) == __WORKING_THREADS.end())
		__WORKING_THREADS.push_back(std::this_thread::get_id());

	if (__ELPASED_HISTORY.find(p_spy.name) != __ELPASED_HISTORY.end())
	{
		__ELPASED_HISTORY[p_spy.name] += std::chrono::duration<double>(p_spy.end - p_spy.start).count();
	}
	else
	{
		__ELPASED_HISTORY[p_spy.name] = std::chrono::duration<double>(p_spy.end - p_spy.start).count();
	}

	if (__CALLS_COUNTER.find(p_spy.name) != __CALLS_COUNTER.end())
	{
		++__CALLS_COUNTER[p_spy.name];
	}
	else
	{
		__CALLS_COUNTER[p_spy.name] = 1;
	}

	__SAVE_MUTEX.unlock();
}

bool GeAnalytics::Profiling::Profiler::IsEnabled()
{
	return __ENABLED;
}

void GeAnalytics::Profiling::Profiler::ToggleEnable()
{
	__ENABLED = !__ENABLED;
}

void GeAnalytics::Profiling::Profiler::Enable()
{
	__ENABLED = true;
}

void GeAnalytics::Profiling::Profiler::Disable()
{
	__ENABLED = false;
}
