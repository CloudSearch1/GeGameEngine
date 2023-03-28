#pragma once

#include <string>
#include <functional>


struct tagOFNA;

namespace GeWindow::Dialogs
{
  //一些可以传递给 FileDialog 实例的标志
	enum class EExplorerFlags
	{
		READONLY                 = 0x00000001,
		OVERWRITEPROMPT          = 0x00000002,
		HIDEREADONLY             = 0x00000004,
		NOCHANGEDIR              = 0x00000008,
		SHOWHELP                 = 0x00000010,
		ENABLEHOOK               = 0x00000020,
		ENABLETEMPLATE           = 0x00000040,
		ENABLETEMPLATEHANDLE     = 0x00000080,
		NOVALIDATE               = 0x00000100,
		ALLOWMULTISELECT         = 0x00000200,
		EXTENSIONDIFFERENT       = 0x00000400,
		PATHMUSTEXIST            = 0x00000800,
		FILEMUSTEXIST            = 0x00001000,
		CREATEPROMPT             = 0x00002000,
		SHAREAWARE               = 0x00004000,
		NOREADONLYRETURN         = 0x00008000,
		NOTESTFILECREATE         = 0x00010000,
		NONETWORKBUTTON          = 0x00020000,
		NOLONGNAMES              = 0x00040000,	// 强制 4.x 模块没有长名称
		EXPLORER                 = 0x00080000,	// 新外观 commdlg
		NODEREFERENCELINKS       = 0x00100000,	
		LONGNAMES                = 0x00200000,	// 为 3.x 模块强制使用长名称
		ENABLEINCLUDENOTIFY      = 0x00400000,	// 发送包含消息到回调
		ENABLESIZING             = 0x00800000,	
		DONTADDTORECENT          = 0x02000000,	
		FORCESHOWHIDDEN          = 0x10000000	  // 显示所有文件，包括系统文件和隐藏文件
	};

	inline EExplorerFlags operator~ (EExplorerFlags a) { return (EExplorerFlags)~(int)a; }
	inline EExplorerFlags operator| (EExplorerFlags a, EExplorerFlags b) { return (EExplorerFlags)((int)a | (int)b); }
	inline EExplorerFlags operator& (EExplorerFlags a, EExplorerFlags b) { return (EExplorerFlags)((int)a & (int)b); }
	inline EExplorerFlags operator^ (EExplorerFlags a, EExplorerFlags b) { return (EExplorerFlags)((int)a ^ (int)b); }
	inline EExplorerFlags& operator|= (EExplorerFlags& a, EExplorerFlags b) { return (EExplorerFlags&)((int&)a |= (int)b); }
	inline EExplorerFlags& operator&= (EExplorerFlags& a, EExplorerFlags b) { return (EExplorerFlags&)((int&)a &= (int)b); }
	inline EExplorerFlags& operator^= (EExplorerFlags& a, EExplorerFlags b) { return (EExplorerFlags&)((int&)a ^= (int)b); }

  //FileDialog 是任何要求用户从磁盘选择文件/将文件保存到磁盘的对话框窗口的基类
	class FileDialog
	{
	public:
		FileDialog(std::function<int(tagOFNA*)> p_callback, const std::string& p_dialogTitle);

    //定义初始目录（FileDialog 将在其中打开）
		void SetInitialDirectory(const std::string& p_initialDirectory);

    //显示文件对话框
		virtual void Show(EExplorerFlags p_flags = EExplorerFlags::DONTADDTORECENT | EExplorerFlags::FILEMUSTEXIST | EExplorerFlags::HIDEREADONLY | EExplorerFlags::NOCHANGEDIR);

    //如果文件操作成功则返回真
		bool HasSucceeded() const;

    //返回选择的文件名（在调用此方法之前确保 HasSucceeded() 返回 true）
		std::string GetSelectedFileName();

    //返回选择的文件路径（在调用此方法之前确保 HasSucceeded() 返回 true）
		std::string GetSelectedFilePath();

    //返回关于最后一个错误的一些信息（确保 HasSucceeded() 在调用此方法之前返回 false）
		std::string GetErrorInfo();

    //如果选择的文件存在则返回真
		bool IsFileExisting() const;

	private:
		void HandleError();

	protected:
		std::function<int(tagOFNA*)> m_callback;
		const std::string m_dialogTitle;
		std::string m_initialDirectory;
		std::string m_filter;
		std::string m_error;
		std::string m_filename;
		std::string m_filepath;
		bool m_succeeded;
	};
}
