/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GL/glew.h>

#include "GeEditor/Panels/AView.h"
#include "GeEditor/Core/EditorActions.h"

GeEditor::Panels::AView::AView
(
	const std::string& p_title,
	bool p_opened,
	const GeUI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings), m_editorRenderer(EDITOR_RENDERER())
{
	m_cameraPosition = { -10.0f, 3.0f, 10.0f };
	m_cameraRotation = GeMaths::FQuaternion({0.0f, 135.0f, 0.0f});

	m_image = &CreateWidget<GeUI::Widgets::Visual::Image>(m_fbo.GetTextureID(), GeMaths::FVector2{ 0.f, 0.f });

    scrollable = false;
}

void GeEditor::Panels::AView::Update(float p_deltaTime)
{
	auto[winWidth, winHeight] = GetSafeSize();

	m_image->size = GeMaths::FVector2(static_cast<float>(winWidth), static_cast<float>(winHeight));

	m_fbo.Resize(winWidth, winHeight);
}

void GeEditor::Panels::AView::_Draw_Impl()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	GeUI::Panels::PanelWindow::_Draw_Impl();

	ImGui::PopStyleVar();
}

void GeEditor::Panels::AView::Render()
{
	FillEngineUBO();

	auto [winWidth, winHeight] = GetSafeSize();

	EDITOR_CONTEXT(shapeDrawer)->SetViewProjection(m_camera.GetProjectionMatrix() * m_camera.GetViewMatrix());

	EDITOR_CONTEXT(renderer)->SetViewPort(0, 0, winWidth, winHeight);

	_Render_Impl();
}

void GeEditor::Panels::AView::SetCameraPosition(const GeMaths::FVector3 & p_position)
{
	m_cameraPosition = p_position;
}

void GeEditor::Panels::AView::SetCameraRotation(const GeMaths::FQuaternion& p_rotation)
{
	m_cameraRotation = p_rotation;
}

const GeMaths::FVector3 & GeEditor::Panels::AView::GetCameraPosition() const
{
	return m_cameraPosition;
}

const GeMaths::FQuaternion& GeEditor::Panels::AView::GetCameraRotation() const
{
	return m_cameraRotation;
}

GeRendering::LowRenderer::Camera & GeEditor::Panels::AView::GetCamera()
{
	return m_camera;
}

std::pair<uint16_t, uint16_t> GeEditor::Panels::AView::GetSafeSize() const
{
	auto result = GetSize() - GeMaths::FVector2{ 0.f, 25.f }; // 25 == title bar height
	return { static_cast<uint16_t>(result.x), static_cast<uint16_t>(result.y) };
}

const GeMaths::FVector3& GeEditor::Panels::AView::GetGridColor() const
{
	return m_gridColor;
}

void GeEditor::Panels::AView::SetGridColor(const GeMaths::FVector3& p_color)
{
	m_gridColor = p_color;
}

void GeEditor::Panels::AView::FillEngineUBO()
{
	auto& engineUBO = *EDITOR_CONTEXT(engineUBO);

	auto[winWidth, winHeight] = GetSafeSize();

	size_t offset = sizeof(GeMaths::FMatrix4); // We skip the model matrix (Which is a special case, modified every draw calls)
	engineUBO.SetSubData(GeMaths::FMatrix4::Transpose(m_camera.GetViewMatrix()), std::ref(offset));
	engineUBO.SetSubData(GeMaths::FMatrix4::Transpose(m_camera.GetProjectionMatrix()), std::ref(offset));
	engineUBO.SetSubData(m_cameraPosition, std::ref(offset));
}

void GeEditor::Panels::AView::PrepareCamera()
{
	auto [winWidth, winHeight] = GetSafeSize();
	m_camera.CacheMatrices(winWidth, winHeight, m_cameraPosition, m_cameraRotation);
}
