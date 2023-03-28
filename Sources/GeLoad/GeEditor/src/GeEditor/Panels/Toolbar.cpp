/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GeUI/Widgets/Layout/Spacing.h>

#include "GeEditor/Panels/Toolbar.h"
#include "GeEditor/Core/EditorActions.h"

#include <GeCore/Global/ServiceLocator.h>
#include <GeCore/ResourceManagement/TextureManager.h>

GeEditor::Panels::Toolbar::Toolbar
(
	const std::string& p_title,
	bool p_opened,
	const GeUI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	std::string iconFolder = ":Textures/Icons/";

	auto& textureManager = GeCore::Global::ServiceLocator::Get<GeCore::ResourceManagement::TextureManager>();

	m_playButton	= &CreateWidget<GeUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Play")->id, GeMaths::FVector2{ 20, 20 });
	m_pauseButton	= &CreateWidget<GeUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Pause")->id, GeMaths::FVector2{ 20, 20 });
	m_stopButton	= &CreateWidget<GeUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Stop")->id, GeMaths::FVector2{ 20, 20 });
	m_nextButton	= &CreateWidget<GeUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Next")->id, GeMaths::FVector2{ 20, 20 });

	CreateWidget<GeUI::Widgets::Layout::Spacing>(0).lineBreak = false;
	auto& refreshButton	= CreateWidget<GeUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Refresh")->id, GeMaths::FVector2{ 20, 20 });

	m_playButton->lineBreak		= false;
	m_pauseButton->lineBreak	= false;
	m_stopButton->lineBreak		= false;
	m_nextButton->lineBreak		= false;
	refreshButton.lineBreak		= false;

	m_playButton->ClickedEvent	+= EDITOR_BIND(StartPlaying);
	m_pauseButton->ClickedEvent	+= EDITOR_BIND(PauseGame);
	m_stopButton->ClickedEvent	+= EDITOR_BIND(StopPlaying);
	m_nextButton->ClickedEvent	+= EDITOR_BIND(NextFrame);
	refreshButton.ClickedEvent	+= EDITOR_BIND(RefreshScripts);

	EDITOR_EVENT(EditorModeChangedEvent) += [this](GeEditor::Core::EditorActions::EEditorMode p_newMode)
	{
		auto enable = [](GeUI::Widgets::Buttons::ButtonImage* p_button, bool p_enable)
		{
			p_button->disabled = !p_enable;
			p_button->tint = p_enable ? GeUI::Types::Color{ 1.0f, 1.0f, 1.0f, 1.0f} : GeUI::Types::Color{1.0f, 1.0f, 1.0f, 0.15f};
		};

		switch (p_newMode)
		{
		case GeEditor::Core::EditorActions::EEditorMode::EDIT:
			enable(m_playButton, true);
			enable(m_pauseButton, false);
			enable(m_stopButton, false);
			enable(m_nextButton, false);
			break;
		case GeEditor::Core::EditorActions::EEditorMode::PLAY:
			enable(m_playButton, false);
			enable(m_pauseButton, true);
			enable(m_stopButton, true);
			enable(m_nextButton, true);
			break;
		case GeEditor::Core::EditorActions::EEditorMode::PAUSE:
			enable(m_playButton, true);
			enable(m_pauseButton, false);
			enable(m_stopButton, true);
			enable(m_nextButton, true);
			break;
		case GeEditor::Core::EditorActions::EEditorMode::FRAME_BY_FRAME:
			enable(m_playButton, true);
			enable(m_pauseButton, false);
			enable(m_stopButton, true);
			enable(m_nextButton, true);
			break;
		}
	};

	EDITOR_EXEC(SetEditorMode(GeEditor::Core::EditorActions::EEditorMode::EDIT));
}

void GeEditor::Panels::Toolbar::_Draw_Impl()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

	GeUI::Panels::PanelWindow::_Draw_Impl();

	ImGui::PopStyleVar();
}