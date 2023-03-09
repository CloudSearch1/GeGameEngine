/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Plugins/ContextualMenu.h"

void GeUI::Plugins::ContextualMenu::Execute()
{
	if (ImGui::BeginPopupContextItem())
	{
		DrawWidgets();
		ImGui::EndPopup();
	}
}

void GeUI::Plugins::ContextualMenu::Close()
{
	ImGui::CloseCurrentPopup();
}
