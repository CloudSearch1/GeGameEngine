#pragma once

#include <string>
#include <functional>


namespace GeUtils::Utils
{
	class String
	{
	public:
		String() = delete;

    //将给定字符串中第一次出现的 p_from 替换为 p_to
		static bool Replace(std::string& p_target, const std::string& p_from, const std::string& p_to);

    //将给定字符串中出现的 p_from 替换为 p_to
		static void ReplaceAll(std::string& p_target, const std::string& p_from, const std::string& p_to);

    //生成满足可用性谓词的唯一字符串
    static std::string GenerateUnique(const std::string& p_source, std::function<bool(std::string)> p_isAvailable);
	};
}
