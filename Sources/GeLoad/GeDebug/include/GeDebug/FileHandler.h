#pragma once

#include <string>
#include <queue>

#include "GeDebug/ILogHandler.h"

namespace GeDebug
{
  //将日志处理成一个文件
	class FileHandler : public ILogHandler
	{
	public:

		void Log(const LogData& p_logData);
	
		static std::string& GetLogFilePath();

		static void SetLogFilePath(const std::string& p_path);

	private:
		static std::string GetLogHeader(ELogLevel p_logLevel);

		static const std::string __DEFAULT_HEADER;
		static const std::string __INFO_HEADER;
		static const std::string __WARNING_HEADER;
		static const std::string __ERROR_HEADER;
		static std::string __APP_LAUNCH_DATE;
		static const std::string __LOG_EXTENSION;

		static std::string LOG_FILE_PATH;
		static std::ofstream OUTPUT_FILE;
	};
}
