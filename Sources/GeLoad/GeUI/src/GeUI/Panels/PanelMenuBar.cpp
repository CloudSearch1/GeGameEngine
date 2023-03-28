/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Panels/PanelMenuBar.h"

void GeUI::Panels::PanelMenuBar::_Draw_Impl()
{
	if (!m_widgets.empty() && ImGui::BeginMainMenuBar())
	{
		DrawWidgets();
		ImGui::EndMainMenuBar();
	}
}