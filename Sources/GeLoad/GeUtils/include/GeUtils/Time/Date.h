#pragma once

#include <string>


namespace GeUtils::Time
{
  //日期系统以字符串格式获取当前日期
	class Date
	{
	public:
		Date() = delete;
    
    //以字符串格式返回当前日期
		static std::string GetDateAsString();
	};
}
