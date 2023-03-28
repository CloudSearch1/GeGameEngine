/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <algorithm>

#include "GeUI/Panels/APanel.h"

uint64_t GeUI::Panels::APanel::__PANEL_ID_INCREMENT = 0;

GeUI::Panels::APanel::APanel()
{
	m_panelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
}

void GeUI::Panels::APanel::Draw()
{
	if (enabled)
		_Draw_Impl();
}

const std::string & GeUI::Panels::APanel::GetPanelID() const
{
	return m_panelID;
}
