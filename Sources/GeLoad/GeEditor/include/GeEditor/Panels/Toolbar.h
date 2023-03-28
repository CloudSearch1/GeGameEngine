/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeUI/Widgets/Buttons/ButtonImage.h>
#include <GeUI/Panels/PanelWindow.h>

namespace GeEditor::Panels
{
	class Toolbar : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Toolbar
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Custom implementation of the draw method
		*/
		void _Draw_Impl() override;

	private:
		GeUI::Widgets::Buttons::ButtonImage* m_playButton;
		GeUI::Widgets::Buttons::ButtonImage* m_pauseButton;
		GeUI::Widgets::Buttons::ButtonImage* m_stopButton;
		GeUI::Widgets::Buttons::ButtonImage* m_nextButton;
	};
}