/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Texts/TextClickable.h"

GeUI::Widgets::Texts::TextClickable::TextClickable(const std::string & p_content) :
	Text(p_content)
{
}

void GeUI::Widgets::Texts::TextClickable::_Draw_Impl()
{
	bool useless = false;

    if (ImGui::Selectable((content + m_widgetID).c_str(), &useless, ImGuiSelectableFlags_AllowDoubleClick))
    {
        if (ImGui::IsMouseDoubleClicked(0))
        {
            DoubleClickedEvent.Invoke();
        }
        else
        {
            ClickedEvent.Invoke();
        }
    }
}
