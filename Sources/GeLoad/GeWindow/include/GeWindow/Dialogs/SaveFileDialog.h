#pragma once

#include "GeWindow/Dialogs/FileDialog.h"

namespace GeWindow::Dialogs
{
  //要求用户将文件保存到磁盘的对话框窗口
	class SaveFileDialog : public FileDialog
	{
	public:
		SaveFileDialog(const std::string& p_dialogTitle);

    //显示文件对话框
		virtual void Show(EExplorerFlags p_flags = EExplorerFlags::DONTADDTORECENT | EExplorerFlags::FILEMUSTEXIST | EExplorerFlags::HIDEREADONLY | EExplorerFlags::NOCHANGEDIR) override;

    //定义保存文件的扩展名
		void DefineExtension(const std::string& p_label, const std::string& p_extension);

	private:
		void AddExtensionToFilePathAndName();

	private:
		std::string m_extension;
	};
}
