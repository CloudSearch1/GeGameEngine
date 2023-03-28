#include "GeDebug/Logger.h"
#include "GeUtils/Time/Date.h"

GeUtils::Eventing::Event<const GeDebug::LogData&> GeDebug::Logger::LogEvent;

std::map<std::string, GeDebug::ConsoleHandler>	GeDebug::Logger::CONSOLE_HANDLER_MAP;
std::map<std::string, GeDebug::FileHandler>		GeDebug::Logger::FILE_HANDLER_MAP;
std::map<std::string, GeDebug::HistoryHandler>	GeDebug::Logger::HISTORY_HANDLER_MAP;

void GeDebug::Logger::Log(const std::string& p_message, ELogLevel p_logLevel, ELogMode p_logMode, std::string p_handlerId)
{
	LogData logData{ p_message, p_logLevel, GeUtils::Time::Date::GetDateAsString() };

	switch (p_logMode)
	{
	case ELogMode::DEFAULT:
	case ELogMode::CONSOLE: LogToHandlerMap<ConsoleHandler>(CONSOLE_HANDLER_MAP, logData, p_handlerId); break;
	case ELogMode::FILE:	LogToHandlerMap<FileHandler>(FILE_HANDLER_MAP, logData, p_handlerId);		break;
	case ELogMode::HISTORY: LogToHandlerMap<HistoryHandler>(HISTORY_HANDLER_MAP, logData, p_handlerId);	break;
	case ELogMode::ALL:
		LogToHandlerMap<ConsoleHandler>(CONSOLE_HANDLER_MAP, logData, p_handlerId);
		LogToHandlerMap<FileHandler>(FILE_HANDLER_MAP, logData, p_handlerId);
		LogToHandlerMap<HistoryHandler>(HISTORY_HANDLER_MAP, logData, p_handlerId);
		break;
	}

	LogEvent.Invoke(logData);
}

GeDebug::ConsoleHandler& GeDebug::Logger::CreateConsoleHandler(std::string p_id)
{
	CONSOLE_HANDLER_MAP.emplace(p_id, GeDebug::ConsoleHandler());
	return CONSOLE_HANDLER_MAP[p_id];
}

GeDebug::FileHandler& GeDebug::Logger::CreateFileHandler(std::string p_id)
{
	FILE_HANDLER_MAP.emplace(p_id, GeDebug::FileHandler());
	return FILE_HANDLER_MAP[p_id];
}

GeDebug::HistoryHandler& GeDebug::Logger::CreateHistoryHandler(std::string p_id)
{
	HISTORY_HANDLER_MAP.emplace(p_id, GeDebug::HistoryHandler());
	return HISTORY_HANDLER_MAP[p_id];
}

GeDebug::ConsoleHandler& GeDebug::Logger::GetConsoleHandler(std::string p_id)
{
	return CONSOLE_HANDLER_MAP[p_id];
}

GeDebug::FileHandler& GeDebug::Logger::GetFileHandler(std::string p_id)
{
	return FILE_HANDLER_MAP[p_id];
}

GeDebug::HistoryHandler& GeDebug::Logger::GetHistoryHandler(std::string p_id)
{
	return HISTORY_HANDLER_MAP[p_id];
}
