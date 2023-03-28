#pragma once

#include "GeWindow/Dialogs/FileDialog.h"

namespace GeWindow::Dialogs
{
  //要求用户从磁盘中选择文件的对话窗口
	class OpenFileDialog : public FileDialog
	{
	public:
		OpenFileDialog(const std::string& p_dialogTitle);

    //将支持的文件类型添加到对话窗口
		void AddFileType(const std::string& p_label, const std::string& p_filter);
	};
}
