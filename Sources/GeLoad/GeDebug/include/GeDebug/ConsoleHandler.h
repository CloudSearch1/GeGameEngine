#pragma once

#include <string>

#include "GeDebug/ILogHandler.h"

namespace GeDebug
{
  //在控制台处理日志
	class ConsoleHandler : public ILogHandler
	{
	public:

		void Log(const LogData& p_logData);

	private:
		static std::string GetLogHeader(ELogLevel p_logLevel);

		static const std::string __DEFAULT_HEADER;
		static const std::string __INFO_HEADER;
		static const std::string __WARNING_HEADER;
		static const std::string __ERROR_HEADER;
	};
}
