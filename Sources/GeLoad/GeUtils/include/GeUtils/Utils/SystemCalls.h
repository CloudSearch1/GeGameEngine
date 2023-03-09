#pragma once

#include <string>


namespace GeUtils::Utils
{
	class SystemCalls
	{
	public:
    //禁用构造函数
    SystemCalls() = delete;

    //在给定路径打开windows资源管理器
		static void ShowInExplorer(const std::string& p_path);

    //使用默认应用程序打开给定文件
		static void OpenFile(const std::string& p_file, const std::string & p_workingDir = "");

    //使用默认应用程序打开给定文件进行编辑
		static void EditFile(const std::string& p_file);

    //使用默认浏览器打开给定的url
		static void OpenURL(const std::string& p_url);
	};
}
