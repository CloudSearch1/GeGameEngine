/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Layout/Dummy.h"
#include "GeUI/Internal/Converter.h"

GeUI::Widgets::Layout::Dummy::Dummy(const GeMaths::FVector2& p_size) : size(p_size)
{
}

void GeUI::Widgets::Layout::Dummy::_Draw_Impl()
{
	ImGui::Dummy(Internal::Converter::ToImVec2(size));
}
