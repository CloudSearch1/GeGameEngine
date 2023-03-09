#pragma once

#include <string>
#include <map>

#include <GeUtils/Eventing/Event.h>

#include "GeDebug/ILogHandler.h"
#include "GeDebug/ConsoleHandler.h"
#include "GeDebug/FileHandler.h"
#include "GeDebug/HistoryHandler.h"

#define OVLOG(message)			GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_DEFAULT,	GeDebug::ELogMode::CONSOLE)
#define OVLOG_INFO(message)		GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_INFO,		GeDebug::ELogMode::CONSOLE)
#define OVLOG_WARNING(message)	GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_WARNING,	GeDebug::ELogMode::CONSOLE)
#define OVLOG_ERROR(message)	GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_ERROR,	GeDebug::ELogMode::CONSOLE)

#define OVFLOG(message)			GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_DEFAULT, 	GeDebug::ELogMode::CONSOLE); GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_DEFAULT, GeDebug::ELogMode::FILE)
#define OVFLOG_INFO(message)	GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_INFO, 	GeDebug::ELogMode::CONSOLE); GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_INFO, 	GeDebug::ELogMode::FILE)
#define OVFLOG_WARNING(message)	GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_WARNING, 	GeDebug::ELogMode::CONSOLE); GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_WARNING, GeDebug::ELogMode::FILE)
#define OVFLOG_ERROR(message)	GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_ERROR, 	GeDebug::ELogMode::CONSOLE); GeDebug::Logger::Log(message, GeDebug::ELogLevel::LOG_ERROR, 	GeDebug::ELogMode::FILE)

namespace GeDebug
{
	class Logger
	{
	public:

		Logger() = delete;

		static void Log(const std::string& p_message, ELogLevel p_logLevel = ELogLevel::LOG_DEFAULT, ELogMode p_logMode = ELogMode::DEFAULT, std::string p_handlerId = "default");

		static ConsoleHandler& CreateConsoleHandler(std::string p_id);

		static FileHandler& CreateFileHandler(std::string p_id);

		static HistoryHandler& CreateHistoryHandler(std::string p_id);

		static ConsoleHandler& GetConsoleHandler(std::string p_id);

		static FileHandler& GetFileHandler(std::string p_id);

		static HistoryHandler& GetHistoryHandler(std::string p_id);

	private:
		template<typename T>
		static void LogToHandlerMap(std::map<std::string, T>& p_map, const LogData& p_data, std::string p_id);

	public:
		static GeUtils::Eventing::Event<const LogData&> LogEvent;

	private:
		static std::map<std::string, ConsoleHandler>	CONSOLE_HANDLER_MAP;
		static std::map<std::string, FileHandler>		FILE_HANDLER_MAP;
		static std::map<std::string, HistoryHandler>	HISTORY_HANDLER_MAP;
	};
}

#include "GeDebug/Logger.inl"
