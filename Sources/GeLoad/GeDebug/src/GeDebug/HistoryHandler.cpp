#include "GeDebug/HistoryHandler.h"

std::queue<GeDebug::LogData> GeDebug::HistoryHandler::LOG_QUEUE;

void GeDebug::HistoryHandler::Log(const LogData& p_logData)
{
	LOG_QUEUE.push(p_logData);
}

std::queue<GeDebug::LogData>& GeDebug::HistoryHandler::GetLogQueue()
{
	return LOG_QUEUE;
}
