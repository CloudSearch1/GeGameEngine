/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeAnalytics/Profiling/Profiler.h>

#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Texts/TextColored.h>
#include <GeUI/Widgets/Selection/CheckBox.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Layout/Columns.h>
#include <GeUI/Widgets/Buttons/Button.h>

namespace GeEditor::Panels
{
	class Profiler : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		* @param p_frequency
		*/
		Profiler
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings,
			float p_frequency
		);

		/**
		* Update profiling information
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Enable or disable the profiler
		* @param p_value
		* @param p_disableLog
		*/
		void Enable(bool p_value, bool p_disableLog = false);

	private:
		GeUI::Types::Color CalculateActionColor(double p_percentage) const;
		std::string GenerateActionString(GeAnalytics::Profiling::ProfilerReport::Action& p_action);

	private:
		enum class EProfilingMode
		{
			DEFAULT,
			CAPTURE
		};

		float m_frequency;
		float m_timer = 0.f;
		float m_fpsTimer = 0.f;
		EProfilingMode m_profilingMode = EProfilingMode::DEFAULT;

		GeAnalytics::Profiling::Profiler m_profiler;

		GeUI::Widgets::AWidget* m_separator;
		GeUI::Widgets::Buttons::Button* m_captureResumeButton;
		GeUI::Widgets::Texts::TextColored* m_fpsText;
		GeUI::Widgets::Texts::TextColored* m_elapsedFramesText;
		GeUI::Widgets::Texts::TextColored* m_elapsedTimeText;
		GeUI::Widgets::Layout::Columns<5>* m_actionList;
	};
}