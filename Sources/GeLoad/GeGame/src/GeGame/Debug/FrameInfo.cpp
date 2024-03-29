#ifdef _DEBUG

#include "GeGame/Debug/FrameInfo.h"

GeGame::Debug::FrameInfo::FrameInfo(GeRendering::Core::Renderer& p_renderer, GeWindow::Window& p_window) :
	m_renderer(p_renderer),
	m_window(p_window)
{
	m_defaultHorizontalAlignment = GeUI::Settings::EHorizontalAlignment::LEFT;
	m_defaultVerticalAlignment = GeUI::Settings::EVerticalAlignment::BOTTOM;
	m_defaultPosition.x = static_cast<float>(p_window.GetSize().first) - 10.f;
	m_defaultPosition.y = static_cast<float>(p_window.GetSize().second) - 10.f;

	m_frameInfo[0] = &CreateWidget<GeUI::Widgets::Texts::TextColored>("", GeUI::Types::Color::Yellow);
	m_frameInfo[1] = &CreateWidget<GeUI::Widgets::Texts::TextColored>("", GeUI::Types::Color::Yellow);
	m_frameInfo[2] = &CreateWidget<GeUI::Widgets::Texts::TextColored>("", GeUI::Types::Color::Yellow);
}

void GeGame::Debug::FrameInfo::Update(float p_deltaTime)
{
	auto& frameInfo = m_renderer.GetFrameInfo();

	m_frameInfo[0]->content = "Triangles: " + std::to_string(frameInfo.polyCount);
	m_frameInfo[1]->content = "Batches: " + std::to_string(frameInfo.batchCount);
	m_frameInfo[2]->content = "Instances: " + std::to_string(frameInfo.instanceCount);

	SetPosition({ 10.0f , static_cast<float>(m_window.GetSize().second) - 10.f });
	SetAlignment(GeUI::Settings::EHorizontalAlignment::LEFT, GeUI::Settings::EVerticalAlignment::BOTTOM);
}

#endif
