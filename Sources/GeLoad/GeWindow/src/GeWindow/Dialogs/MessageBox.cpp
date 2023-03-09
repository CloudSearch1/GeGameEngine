#include <windows.h>

#include "GeWindow/Dialogs/MessageBox.h"

#undef MessageBox

GeWindow::Dialogs::MessageBox::MessageBox(std::string p_title, std::string p_message, EMessageType p_messageType, EButtonLayout p_buttonLayout, bool p_autoSpawn) :
	m_title(p_title),
	m_message(p_message),
	m_buttonLayout(p_buttonLayout),
	m_messageType(p_messageType)
{
	if (p_autoSpawn)
		Spawn();
}

const GeWindow::Dialogs::MessageBox::EUserAction& GeWindow::Dialogs::MessageBox::GetUserAction() const
{
	return m_userResult;
}

void GeWindow::Dialogs::MessageBox::Spawn()
{
	int msgboxID = MessageBoxA
	(
		nullptr,
		static_cast<LPCSTR>(m_message.c_str()),
		static_cast<LPCSTR>(m_title.c_str()),
		static_cast<UINT>(m_messageType) | static_cast<UINT>(m_buttonLayout) | MB_DEFBUTTON2
	);

	m_userResult = static_cast<EUserAction>(msgboxID);
}
