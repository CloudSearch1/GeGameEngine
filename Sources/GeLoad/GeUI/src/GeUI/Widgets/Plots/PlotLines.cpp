/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/Plots/PlotLines.h"
#include "GeUI/Internal/Converter.h"

GeUI::Widgets::Plots::PlotLines::PlotLines
(
	const std::vector<float>& p_data,
	float p_minScale,
	float p_maxScale,
	const GeMaths::FVector2& p_size,
	const std::string& p_overlay,
	const std::string& p_label,
	int p_forceHover
) : APlot(p_data, p_minScale, p_maxScale, p_size, p_overlay, p_label, p_forceHover)
{
}

void GeUI::Widgets::Plots::PlotLines::_Draw_Impl()
{
	ImGui::PlotLines((label + m_widgetID).c_str(), data.data(), static_cast<int>(data.size()), 0, overlay.c_str(), minScale, maxScale, Internal::Converter::ToImVec2(size), sizeof(float), forceHover);
}
