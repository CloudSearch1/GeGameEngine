/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Layout/Spacing.h"

GeUI::Widgets::Layout::Spacing::Spacing(uint16_t p_spaces) : spaces(p_spaces)
{
}

void GeUI::Widgets::Layout::Spacing::_Draw_Impl()
{
	for (uint16_t i = 0; i < spaces; ++i)
	{
		ImGui::Spacing();

		if (i + 1 < spaces)
			ImGui::SameLine();
	}
}
