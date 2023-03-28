#ifdef _DEBUG

#include "GeGame/Debug/DriverInfo.h"

GeGame::Debug::DriverInfo::DriverInfo(GeRendering::Core::Renderer& p_renderer, GeWindow::Window& p_window)
{
	m_defaultHorizontalAlignment = GeUI::Settings::EHorizontalAlignment::RIGHT;
	m_defaultVerticalAlignment = GeUI::Settings::EVerticalAlignment::BOTTOM;
	m_defaultPosition.x = static_cast<float>(p_window.GetSize().first) - 10.f;
	m_defaultPosition.y = static_cast<float>(p_window.GetSize().second) - 10.f;

	CreateWidget<GeUI::Widgets::Texts::TextColored>("Vendor: "	+ p_renderer.GetString(GL_VENDOR), GeUI::Types::Color::Yellow);
	CreateWidget<GeUI::Widgets::Texts::TextColored>("Hardware: " + p_renderer.GetString(GL_RENDERER), GeUI::Types::Color::Yellow);
	CreateWidget<GeUI::Widgets::Texts::TextColored>("OpenGL Version: " + p_renderer.GetString(GL_VERSION), GeUI::Types::Color::Yellow);
	CreateWidget<GeUI::Widgets::Texts::TextColored>("GLSL Version: " + p_renderer.GetString(GL_SHADING_LANGUAGE_VERSION), GeUI::Types::Color::Yellow);
}

#endif
