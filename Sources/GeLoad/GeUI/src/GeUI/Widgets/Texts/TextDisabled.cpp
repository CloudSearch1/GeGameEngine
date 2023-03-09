/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Texts/TextDisabled.h"

GeUI::Widgets::Texts::TextDisabled::TextDisabled(const std::string & p_content) :
	Text(p_content)
{
}

void GeUI::Widgets::Texts::TextDisabled::_Draw_Impl()
{
	ImGui::TextDisabled(content.c_str());
}
