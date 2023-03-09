#pragma once

#include <GeUI/Panels/PanelUndecorated.h>
#include <GeUI/Widgets/Texts/TextColored.h>

#include <GeWindow/Window.h>

namespace GeGame::Utils
{
	class FPSCounter : public GeUI::Panels::PanelUndecorated
	{
	public:
		FPSCounter(GeWindow::Window& p_window);

		void Update(float p_deltaTime);

	private:
		GeUI::Widgets::Texts::TextColored m_text;

		GeWindow::Window& m_window;
		float m_elapsed = 0.0f;
		uint32_t m_frames = 0;
	};
}
