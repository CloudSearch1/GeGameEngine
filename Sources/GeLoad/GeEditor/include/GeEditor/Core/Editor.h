#pragma once

#include <GeRendering/LowRenderer/Camera.h>

#include "GeEditor/Core/EditorRenderer.h"
#include "GeEditor/Core/EditorActions.h"
#include "GeEditor/Core/PanelsManager.h"

#include <GeUI/Modules/Canvas.h>

#include "GeEditor/Core/Context.h"

#include <GeAnalytics/Profiling/ProfilerSpy.h>

namespace GeEditor::Core
{
	class Editor
	{
	public:
		Editor(Context& p_context);

		~Editor();

		void SetupUI();

		void PreUpdate();

		void Update(float p_deltaTime);

		void HandleGlobalShortcuts();

		void UpdateCurrentEditorMode(float p_deltaTime);

		void UpdatePlayMode(float p_deltaTime);

		void UpdateEditMode(float p_deltaTime);

		void UpdateEditorPanels(float p_deltaTime);

		void PrepareRendering(float p_deltaTime);

		void RenderViews(float p_deltaTime);

		void RenderEditorUI(float p_deltaTime);
		
		void PostUpdate();

	private:
		uint64_t m_elapsedFrames = 0;
		GeUI::Modules::Canvas			m_canvas;
		GeEditor::Core::Context&		m_context;
		GeEditor::Core::EditorRenderer	m_editorRenderer;
		GeEditor::Core::PanelsManager	m_panelsManager;
		GeEditor::Core::EditorActions	m_editorActions;
	};
}
