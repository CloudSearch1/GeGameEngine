/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Internal/Converter.h"

ImVec4 GeUI::Internal::Converter::ToImVec4(const Types::Color & p_value)
{
	return ImVec4(p_value.r, p_value.g, p_value.b, p_value.a);
}

GeUI::Types::Color GeUI::Internal::Converter::ToColor(const ImVec4 & p_value)
{
	return Types::Color(p_value.x, p_value.y, p_value.z, p_value.w);
}

ImVec2 GeUI::Internal::Converter::ToImVec2(const GeMaths::FVector2 & p_value)
{
	return ImVec2(p_value.x, p_value.y);
}

GeMaths::FVector2 GeUI::Internal::Converter::ToFVector2(const ImVec2 & p_value)
{
	return GeMaths::FVector2(p_value.x, p_value.y);
}
