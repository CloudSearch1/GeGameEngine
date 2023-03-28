/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Layout/GroupCollapsable.h"
#include "GeUI/ImGui/imgui_internal.h"

GeUI::Widgets::Layout::GroupCollapsable::GroupCollapsable(const std::string & p_name) :
	name(p_name)
{
}

void GeUI::Widgets::Layout::GroupCollapsable::_Draw_Impl()
{
	bool previouslyOpened = opened;

	if (ImGui::CollapsingHeader(name.c_str(), closable ? &opened : nullptr))
		Group::_Draw_Impl();

	if (opened != previouslyOpened)
	{
		if (opened)
			OpenEvent.Invoke();
		else
			CloseEvent.Invoke();
	}
}
