/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Buttons/Button.h"
#include "GeUI/Internal/Converter.h"
#include "GeUI/ImGui/imgui_internal.h"

GeUI::Widgets::Buttons::Button::Button(const std::string& p_label, const GeMaths::FVector2& p_size, bool p_disabled) :
	label(p_label), size(p_size), disabled(p_disabled)
{
	auto& style = ImGui::GetStyle();

	idleBackgroundColor		= Internal::Converter::ToColor(style.Colors[ImGuiCol_Button]);
	hoveredBackgroundColor	= Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonHovered]);
	clickedBackgroundColor	= Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonActive]);
	textColor				= Internal::Converter::ToColor(style.Colors[ImGuiCol_Text]);
}

void GeUI::Widgets::Buttons::Button::_Draw_Impl()
{
	auto& style = ImGui::GetStyle();

	auto defaultIdleColor		= style.Colors[ImGuiCol_Button];
	auto defaultHoveredColor	= style.Colors[ImGuiCol_ButtonHovered];
	auto defaultClickedColor	= style.Colors[ImGuiCol_ButtonActive];
	auto defaultTextColor		= style.Colors[ImGuiCol_Text];

	style.Colors[ImGuiCol_Button]			= GeUI::Internal::Converter::ToImVec4(idleBackgroundColor);
	style.Colors[ImGuiCol_ButtonHovered]	= GeUI::Internal::Converter::ToImVec4(hoveredBackgroundColor);
	style.Colors[ImGuiCol_ButtonActive]		= GeUI::Internal::Converter::ToImVec4(clickedBackgroundColor);
	style.Colors[ImGuiCol_Text]				= GeUI::Internal::Converter::ToImVec4(textColor);

	if (ImGui::ButtonEx((label + m_widgetID).c_str(), Internal::Converter::ToImVec2(size), disabled ? ImGuiButtonFlags_Disabled : 0))
		ClickedEvent.Invoke();

	style.Colors[ImGuiCol_Button]			= defaultIdleColor;
	style.Colors[ImGuiCol_ButtonHovered]	= defaultHoveredColor;
	style.Colors[ImGuiCol_ButtonActive]		= defaultClickedColor;
	style.Colors[ImGuiCol_Text]				= defaultTextColor;
}
