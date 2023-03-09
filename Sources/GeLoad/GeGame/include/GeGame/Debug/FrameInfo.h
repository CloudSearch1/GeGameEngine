#pragma once

#ifdef _DEBUG

#include <GeRendering/Core/Renderer.h>
#include <GeWindow/Window.h>

#include <GeUI/Panels/PanelUndecorated.h>
#include <GeUI/Widgets/Texts/TextColored.h>

namespace GeGame::Debug
{
	class FrameInfo : public GeUI::Panels::PanelUndecorated
	{
	public:
		FrameInfo(GeRendering::Core::Renderer& p_renderer, GeWindow::Window& p_window);

		void Update(float p_deltaTime);

	private:
		GeRendering::Core::Renderer&	m_renderer;
		GeWindow::Window&			m_window;

		GeUI::Widgets::Texts::TextColored* m_frameInfo[3];
	};
}

#endif
