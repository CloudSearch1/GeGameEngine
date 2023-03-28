/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Visual/Image.h"
#include "GeUI/Internal/Converter.h"

GeUI::Widgets::Visual::Image::Image(uint32_t p_textureID, const GeMaths::FVector2& p_size) :
	textureID{ p_textureID }, size(p_size)
{
	
}

void GeUI::Widgets::Visual::Image::_Draw_Impl()
{
	ImGui::Image(textureID.raw, Internal::Converter::ToImVec2(size), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
}
