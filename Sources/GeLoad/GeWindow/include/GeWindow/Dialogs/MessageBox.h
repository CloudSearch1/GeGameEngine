#pragma once

#include <string>


//防止枚举和类名被标准宏替换
#undef MessageBox
#undef ERROR
#undef IGNORE

namespace GeWindow::Dialogs
{
  //显示一个包含系统图标的模态对话框，
  //一组按钮和一条简短的特定于应用程序的消息，
  //例如状态或错误信息
	class MessageBox
	{
	public:
    //为 MessageBox 实例定义一些严重级别
		enum class EMessageType
		{
			QUESTION	  = 0x00000020L,
			INFORMATION = 0x00000040L,
			WARNING		  = 0x00000030L,
			ERROR		    = 0x00000010L
		};

		/**
		* Defines some button layouts for MessageBox instances
		*/
		enum class EButtonLayout
		{
			OK							            = 0x00000000L,
			OK_CANCEL					          = 0x00000001L,
			YES_NO						          = 0x00000004L,
			YES_NO_CANCEL				        = 0x00000003L,
			RETRY_CANCEL				        = 0x00000005L,
			ABORT_RETRY_IGNORE			    = 0x00000002L,
			CANCEL_TRYAGAIN_CONTINUE	  = 0x00000006L,
			HELP						            = 0x00004000L
		};

    //定义了 MessageBox 应该提供的一些动作
		enum class EUserAction
		{
			OK			    = 1,
			CANCEL	    = 2,
			YES			    = 6,
			NO			    = 7,
			CONTINUE	  = 11,
			IGNORE		  = 5,
			RETRY		    = 4,
			TRYAGAIN	  = 10
		};

		MessageBox(std::string p_title, std::string p_message, EMessageType p_messageType = EMessageType::INFORMATION, EButtonLayout p_buttonLayout = EButtonLayout::OK, bool p_autoSpawn = true);

    //在屏幕上显示消息框
		void Spawn();

    //返回用户操作
		const EUserAction& GetUserAction() const;

	private:
		std::string		m_title;
		std::string		m_message;
		EButtonLayout	m_buttonLayout;
		EMessageType	m_messageType;
		EUserAction		m_userResult;
	};
}
