#include "GeUtils/Utils/PathParser.h"
#include "GeUtils/Utils/SystemCalls.h"

#include <Windows.h>

namespace GeUtils::Utils
{
  void SystemCalls::ShowInExplorer(const std::string& p_path)
  {
    ShellExecuteA(NULL, "open", PathParser::MakeWindowsStyle(p_path).c_str(), NULL, NULL, SW_SHOWNORMAL);
  }

  void SystemCalls::OpenFile(const std::string& p_file, const std::string& p_workingDir)
  {
    ShellExecuteA(NULL, "open", PathParser::MakeWindowsStyle(p_file).c_str(), NULL,
      p_workingDir.empty() ? NULL : PathParser::MakeWindowsStyle(p_workingDir).c_str(),
      SW_SHOWNORMAL);
  }

  void SystemCalls::EditFile(const std::string& p_file)
  {
    ShellExecuteW(NULL, NULL, std::wstring(p_file.begin(), p_file.end()).c_str(), NULL, NULL, SW_NORMAL);
  }

  void SystemCalls::OpenURL(const std::string& p_url)
  {
    ShellExecute(0, 0, p_url.c_str(), 0, 0, SW_SHOW);
  }

}
