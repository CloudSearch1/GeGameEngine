/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "GeUI/Panels/APanelTransformable.h"
#include "GeUI/Internal/Converter.h"

GeUI::Panels::APanelTransformable::APanelTransformable
(
	const GeMaths::FVector2& p_defaultPosition,
	const GeMaths::FVector2& p_defaultSize,
	Settings::EHorizontalAlignment p_defaultHorizontalAlignment,
	Settings::EVerticalAlignment p_defaultVerticalAlignment,
	bool p_ignoreConfigFile
) :
	m_defaultPosition(p_defaultPosition),
	m_defaultSize(p_defaultSize),
	m_defaultHorizontalAlignment(p_defaultHorizontalAlignment),
	m_defaultVerticalAlignment(p_defaultVerticalAlignment),
	m_ignoreConfigFile(p_ignoreConfigFile)
{
}

void GeUI::Panels::APanelTransformable::SetPosition(const GeMaths::FVector2& p_position)
{
	m_position = p_position;
	m_positionChanged = true;
}

void GeUI::Panels::APanelTransformable::SetSize(const GeMaths::FVector2& p_size)
{
	m_size = p_size;
	m_sizeChanged = true;
}

void GeUI::Panels::APanelTransformable::SetAlignment(Settings::EHorizontalAlignment p_horizontalAlignment, Settings::EVerticalAlignment p_verticalAligment)
{
	m_horizontalAlignment = p_horizontalAlignment;
	m_verticalAlignment = p_verticalAligment;
	m_alignmentChanged = true;
}

const GeMaths::FVector2 & GeUI::Panels::APanelTransformable::GetPosition() const
{
	return m_position;
}

const GeMaths::FVector2 & GeUI::Panels::APanelTransformable::GetSize() const
{
	return m_size;
}

GeUI::Settings::EHorizontalAlignment GeUI::Panels::APanelTransformable::GetHorizontalAlignment() const
{
	return m_horizontalAlignment;
}

GeUI::Settings::EVerticalAlignment GeUI::Panels::APanelTransformable::GetVerticalAlignment() const
{
	return m_verticalAlignment;
}

void GeUI::Panels::APanelTransformable::UpdatePosition()
{
	if (m_defaultPosition.x != -1.f && m_defaultPosition.y != 1.f)
	{
		GeMaths::FVector2 offsettedDefaultPos = m_defaultPosition + CalculatePositionAlignmentOffset(true);
		ImGui::SetWindowPos(Internal::Converter::ToImVec2(offsettedDefaultPos), m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
	}

	if (m_positionChanged || m_alignmentChanged)
	{
		GeMaths::FVector2 offset = CalculatePositionAlignmentOffset(false);
		GeMaths::FVector2 offsettedPos(m_position.x + offset.x, m_position.y + offset.y);
		ImGui::SetWindowPos(Internal::Converter::ToImVec2(offsettedPos), ImGuiCond_Always);
		m_positionChanged = false;
		m_alignmentChanged = false;
	}
}

void GeUI::Panels::APanelTransformable::UpdateSize()
{
	/*
	if (m_defaultSize.x != -1.f && m_defaultSize.y != 1.f)
		ImGui::SetWindowSize(Internal::Converter::ToImVec2(m_defaultSize), m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
	*/
	if (m_sizeChanged)
	{
		ImGui::SetWindowSize(Internal::Converter::ToImVec2(m_size), ImGuiCond_Always);
		m_sizeChanged = false;
	}
}

void GeUI::Panels::APanelTransformable::CopyImGuiPosition()
{
	m_position = Internal::Converter::ToFVector2(ImGui::GetWindowPos());
}

void GeUI::Panels::APanelTransformable::CopyImGuiSize()
{
	m_size = Internal::Converter::ToFVector2(ImGui::GetWindowSize());
}

void GeUI::Panels::APanelTransformable::Update()
{
	if (!m_firstFrame)
	{
		if (!autoSize)
			UpdateSize();
		CopyImGuiSize();

		UpdatePosition();
		CopyImGuiPosition();
	}

	m_firstFrame = false;
}

GeMaths::FVector2 GeUI::Panels::APanelTransformable::CalculatePositionAlignmentOffset(bool p_default)
{
	GeMaths::FVector2 result(0.0f, 0.0f);

	switch (p_default ? m_defaultHorizontalAlignment : m_horizontalAlignment)
	{
	case GeUI::Settings::EHorizontalAlignment::CENTER:
		result.x -= m_size.x / 2.0f;
		break;
	case GeUI::Settings::EHorizontalAlignment::RIGHT:
		result.x -= m_size.x;
		break;
	}

	switch (p_default ? m_defaultVerticalAlignment : m_verticalAlignment)
	{
	case GeUI::Settings::EVerticalAlignment::MIDDLE:
		result.y -= m_size.y / 2.0f;
		break;
	case GeUI::Settings::EVerticalAlignment::BOTTOM:
		result.y -= m_size.y;
		break;
	}

	return result;
}
