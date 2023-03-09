/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <algorithm>

#include "GeEditor/Panels/Console.h"
#include "GeEditor/Core/EditorActions.h"

#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Selection/CheckBox.h>
#include <GeUI/Widgets/Visual/Separator.h>
#include <GeUI/Widgets/Layout/Spacing.h>

using namespace GeUI::Panels;
using namespace GeUI::Widgets;

std::pair<GeUI::Types::Color, std::string> GetWidgetSettingsFromLogData(const GeDebug::LogData& p_logData)
{
	GeUI::Types::Color logColor;
	std::string logHeader;
	std::string logDateFormated = "[";
	bool isSecondPart = false;
	std::for_each(p_logData.date.begin(), p_logData.date.end(), [&logDateFormated, &isSecondPart](char c)
	{ 
		if (isSecondPart)
			logDateFormated.push_back(c == '-' ? ':' : c);

		if (c == '_')
			isSecondPart = true;
	});

	logDateFormated += "] ";

	switch (p_logData.logLevel)
	{
	default:
	case GeDebug::ELogLevel::LOG_DEFAULT:	return { { 1.f, 1.f, 1.f, 1.f }, logDateFormated };
	case GeDebug::ELogLevel::LOG_INFO:		return { { 0.f, 1.f, 1.f, 1.f }, logDateFormated };
	case GeDebug::ELogLevel::LOG_WARNING:	return { { 1.f, 1.f, 0.f, 1.f }, logDateFormated };
	case GeDebug::ELogLevel::LOG_ERROR:		return { { 1.f, 0.f, 0.f, 1.f }, logDateFormated };
	}
}

GeEditor::Panels::Console::Console
(
	const std::string& p_title,
	bool p_opened,
	const GeUI::Settings::PanelWindowSettings& p_windowSettings
) :
	PanelWindow(p_title, p_opened, p_windowSettings)
{
	allowHorizontalScrollbar = true;

	auto& clearButton = CreateWidget<Buttons::Button>("Clear");
	clearButton.size = { 50.f, 0.f };
	clearButton.idleBackgroundColor = { 0.5f, 0.f, 0.f };
	clearButton.ClickedEvent += std::bind(&Console::Clear, this);
	clearButton.lineBreak = false;

	auto& clearOnPlay = CreateWidget<Selection::CheckBox>(m_clearOnPlay, "Auto clear on play");

	CreateWidget<Layout::Spacing>(5).lineBreak = false;

	auto& enableDefault = CreateWidget<Selection::CheckBox>(true, "Default");
	auto& enableInfo = CreateWidget<Selection::CheckBox>(true, "Info");
	auto& enableWarning = CreateWidget<Selection::CheckBox>(true, "Warning");
	auto& enableError = CreateWidget<Selection::CheckBox>(true, "Error");

	clearOnPlay.lineBreak = false;
	enableDefault.lineBreak = false;
	enableInfo.lineBreak = false;
	enableWarning.lineBreak = false;
	enableError.lineBreak = true;

	clearOnPlay.ValueChangedEvent += [this](bool p_value) { m_clearOnPlay = p_value; };
	enableDefault.ValueChangedEvent += std::bind(&Console::SetShowDefaultLogs, this, std::placeholders::_1);
	enableInfo.ValueChangedEvent += std::bind(&Console::SetShowInfoLogs, this, std::placeholders::_1);
	enableWarning.ValueChangedEvent += std::bind(&Console::SetShowWarningLogs, this, std::placeholders::_1);
	enableError.ValueChangedEvent += std::bind(&Console::SetShowErrorLogs, this, std::placeholders::_1);

	CreateWidget<Visual::Separator>();

	m_logGroup = &CreateWidget<Layout::Group>();
    m_logGroup->ReverseDrawOrder();

	EDITOR_EVENT(PlayEvent) += std::bind(&Console::ClearOnPlay, this);

	GeDebug::Logger::LogEvent += std::bind(&Console::OnLogIntercepted, this, std::placeholders::_1);
}

void GeEditor::Panels::Console::OnLogIntercepted(const GeDebug::LogData & p_logData)
{
	auto[logColor, logDate] = GetWidgetSettingsFromLogData(p_logData);

	auto& consoleItem1 = m_logGroup->CreateWidget<Texts::TextColored>(logDate + "\t" + p_logData.message, logColor);

	consoleItem1.enabled = IsAllowedByFilter(p_logData.logLevel);

	m_logTextWidgets[&consoleItem1] = p_logData.logLevel;
}

void GeEditor::Panels::Console::ClearOnPlay()
{
	if (m_clearOnPlay)
		Clear();
}

void GeEditor::Panels::Console::Clear()
{
	m_logTextWidgets.clear();
	m_logGroup->RemoveAllWidgets();
}

void GeEditor::Panels::Console::FilterLogs()
{
	for (const auto&[widget, logLevel] : m_logTextWidgets)
		widget->enabled = IsAllowedByFilter(logLevel);
}

bool GeEditor::Panels::Console::IsAllowedByFilter(GeDebug::ELogLevel p_logLevel)
{
	switch (p_logLevel)
	{
	case GeDebug::ELogLevel::LOG_DEFAULT:	return m_showDefaultLog;
	case GeDebug::ELogLevel::LOG_INFO:		return m_showInfoLog;
	case GeDebug::ELogLevel::LOG_WARNING:	return m_showWarningLog;
	case GeDebug::ELogLevel::LOG_ERROR:		return m_showErrorLog;
	}

	return false;
}

void GeEditor::Panels::Console::SetShowDefaultLogs(bool p_value)
{
	m_showDefaultLog = p_value;
	FilterLogs();
}

void GeEditor::Panels::Console::SetShowInfoLogs(bool p_value)
{
	m_showInfoLog = p_value;
	FilterLogs();
}

void GeEditor::Panels::Console::SetShowWarningLogs(bool p_value)
{
	m_showWarningLog = p_value;
	FilterLogs();
}

void GeEditor::Panels::Console::SetShowErrorLogs(bool p_value)
{
	m_showErrorLog = p_value;
	FilterLogs();
}
