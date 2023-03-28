/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Texts/TextWrapped.h"

GeUI::Widgets::Texts::TextWrapped::TextWrapped(const std::string & p_content) :
	Text(p_content)
{
}

void GeUI::Widgets::Texts::TextWrapped::_Draw_Impl()
{
	ImGui::TextWrapped(content.c_str());
}
