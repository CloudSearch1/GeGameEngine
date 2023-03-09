/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Widgets/AWidget.h"

uint64_t GeUI::Widgets::AWidget::__WIDGET_ID_INCREMENT = 0;

GeUI::Widgets::AWidget::AWidget()
{
	m_widgetID = "##" + std::to_string(__WIDGET_ID_INCREMENT++);
}

void GeUI::Widgets::AWidget::LinkTo(const AWidget& p_widget)
{
	m_widgetID = p_widget.m_widgetID;
}

void GeUI::Widgets::AWidget::Destroy()
{
	m_destroyed = true;
}

bool GeUI::Widgets::AWidget::IsDestroyed() const
{
	return m_destroyed;
}

void GeUI::Widgets::AWidget::SetParent(Internal::WidgetContainer * p_parent)
{
	m_parent = p_parent;
}

bool GeUI::Widgets::AWidget::HasParent() const
{
	return m_parent;
}

GeUI::Internal::WidgetContainer * GeUI::Widgets::AWidget::GetParent()
{
	return m_parent;
}

void GeUI::Widgets::AWidget::Draw()
{
	if (enabled)
	{
		_Draw_Impl();

		if (m_autoExecutePlugins)
			ExecutePlugins();

		if (!lineBreak)
			ImGui::SameLine();
	}
}
