#pragma once

#include <string>
#include <queue>

#include "ILogHandler.h"

namespace GeDebug
{
	class HistoryHandler : public ILogHandler
	{
	public:

		void Log(const LogData& p_logData);

		static std::queue<LogData>& GetLogQueue();

	private:

		static std::queue<LogData> LOG_QUEUE;
	};
}
