/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GeDebug/Logger.h>

#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Layout/Group.h>
#include <GeUI/Widgets/Texts/TextColored.h>

namespace GeEditor::Panels
{
	class Console : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Console
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Method called when a log event occured
		* @param p_logData
		*/
		void OnLogIntercepted(const GeDebug::LogData& p_logData);

		/**
		* Called when the scene plays. It will clear the console if the "Clear on play" settings is on
		*/
		void ClearOnPlay();

		/**
		* Clear the console
		*/
		void Clear();

		/**
		* Filter logs using defined filters
		*/
		void FilterLogs();

		/**
		* Verify if a given log level is allowed by the current filter
		* @param p_logLevel
		*/
		bool IsAllowedByFilter(GeDebug::ELogLevel p_logLevel);

	private:
		void SetShowDefaultLogs(bool p_value);
		void SetShowInfoLogs(bool p_value);
		void SetShowWarningLogs(bool p_value);
		void SetShowErrorLogs(bool p_value);

	private:
		GeUI::Widgets::Layout::Group* m_logGroup;
		std::unordered_map<GeUI::Widgets::Texts::TextColored*, GeDebug::ELogLevel> m_logTextWidgets;

		bool m_clearOnPlay = true;
		bool m_showDefaultLog = true;
		bool m_showInfoLog = true;
		bool m_showWarningLog = true;
		bool m_showErrorLog = true;
	};
}