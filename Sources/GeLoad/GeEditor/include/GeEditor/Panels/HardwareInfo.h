/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Plots/PlotLines.h>
#include <GeUI/Widgets/Plots/PlotHistogram.h>

namespace GeAnalytics::Hardware { class HardwareInfo; }

namespace GeEditor::Panels
{
	class HardwareInfo : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		* @param p_logFrequency
		* @param p_maxElements
		* @param p_displayMode
		*/
		HardwareInfo
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings,
			float p_logFrequency,
			size_t p_maxElements
		);

		/**
		* Destructor
		*/
		~HardwareInfo();

		/**
		* Update hardware info
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

	private:
		float p_updateTimer = 0.f;
		float m_logFrequency;
		size_t m_maxElements;
		GeUI::Widgets::Plots::APlot* m_cpuUsage;
		GeUI::Widgets::Plots::APlot* m_gpuUsage;
		GeUI::Widgets::Plots::APlot* m_ramUsage;
		GeAnalytics::Hardware::HardwareInfo* m_hardwareInfo;
	};
}