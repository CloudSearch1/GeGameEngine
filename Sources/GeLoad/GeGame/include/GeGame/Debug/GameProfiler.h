#pragma once

#ifdef _DEBUG

#include <GeRendering/Core/Renderer.h>
#include <GeWindow/Window.h>

#include <GeAnalytics/Profiling/Profiler.h>
#include <GeUI/Panels/PanelUndecorated.h>
#include <GeUI/Widgets/Texts/TextColored.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Buttons/Button.h>

namespace GeGame::Debug
{
	class GameProfiler : public GeUI::Panels::PanelUndecorated
	{
	public:
		GameProfiler(GeWindow::Window& p_window, float p_frequency);

		void Update(float p_deltaTime);
	

	private:
		GeUI::Types::Color CalculateActionColor(double p_percentage) const;
		std::string GenerateActionString(GeAnalytics::Profiling::ProfilerReport::Action& p_action);

	private:

		float m_frequency;
		float m_timer = 0.f;

		GeAnalytics::Profiling::Profiler m_profiler;

		GeWindow::Window& m_window;
		GeUI::Widgets::AWidget* m_separator;
		GeUI::Widgets::Texts::TextColored* m_elapsedFramesText;
		GeUI::Widgets::Texts::TextColored* m_elapsedTimeText;
		GeUI::Widgets::Layout::Group* m_actionList;
	};
}

#endif
