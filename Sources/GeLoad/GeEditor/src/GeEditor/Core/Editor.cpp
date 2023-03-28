#include <GeAnalytics/Profiling/ProfilerSpy.h>
#include <GePhysics/Core/PhysicsEngine.h>

#include "GeEditor/Core/Editor.h"
#include "GeEditor/Panels/MenuBar.h"
#include "GeEditor/Panels/AssetBrowser.h"
#include "GeEditor/Panels/HardwareInfo.h"
#include "GeEditor/Panels/Profiler.h"
#include "GeEditor/Panels/Console.h"
#include "GeEditor/Panels/Inspector.h"
#include "GeEditor/Panels/Hierarchy.h"
#include "GeEditor/Panels/SceneView.h"
#include "GeEditor/Panels/GameView.h"
#include "GeEditor/Panels/AssetView.h"
#include "GeEditor/Panels/Toolbar.h"
#include "GeEditor/Panels/MaterialEditor.h"
#include "GeEditor/Panels/ProjectSettings.h"
#include "GeEditor/Panels/AssetProperties.h"

using namespace GeCore::ResourceManagement;
using namespace GeEditor::Panels;
using namespace GeRendering::Resources::Loaders;
using namespace GeRendering::Resources::Parsers;

GeEditor::Core::Editor::Editor(Context& p_context) : 
	m_context(p_context),
	m_editorRenderer(p_context),
	m_panelsManager(m_canvas),
	m_editorActions(m_context, m_editorRenderer, m_panelsManager)
{
	SetupUI();

	m_context.sceneManager.LoadEmptyLightedScene();
}

GeEditor::Core::Editor::~Editor()
{
	m_context.sceneManager.UnloadCurrentScene();
}

void GeEditor::Core::Editor::SetupUI()
{
	GeUI::Settings::PanelWindowSettings settings;
	settings.closable = true;
	settings.collapsable = true;
	settings.dockable = true;

	m_panelsManager.CreatePanel<GeEditor::Panels::MenuBar>("Menu Bar");
	m_panelsManager.CreatePanel<GeEditor::Panels::AssetBrowser>("Asset Browser", true, settings, m_context.engineAssetsPath, m_context.projectAssetsPath, m_context.projectScriptsPath);
	m_panelsManager.CreatePanel<GeEditor::Panels::HardwareInfo>("Hardware Info", false, settings, 0.2f, 50);
	m_panelsManager.CreatePanel<GeEditor::Panels::Profiler>("Profiler", true, settings, 0.25f);
	m_panelsManager.CreatePanel<GeEditor::Panels::Console>("Console", true, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::Hierarchy>("Hierarchy", true, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::Inspector>("Inspector", true, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::SceneView>("Scene View", true, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::GameView>("Game View", true, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::AssetView>("Asset View", false, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::Toolbar>("Toolbar", true, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::MaterialEditor>("Material Editor", false, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::ProjectSettings>("Project Settings", false, settings);
	m_panelsManager.CreatePanel<GeEditor::Panels::AssetProperties>("Asset Properties", false, settings);

	m_canvas.MakeDockspace(true);
	m_context.uiManager->SetCanvas(m_canvas);
}

void GeEditor::Core::Editor::PreUpdate()
{
	PROFILER_SPY("Editor Pre-Update");

	m_context.device->PollEvents();
	m_context.renderer->SetClearColor(0.f, 0.f, 0.f);
	m_context.renderer->Clear();
}

void GeEditor::Core::Editor::Update(float p_deltaTime)
{
	HandleGlobalShortcuts();
	UpdateCurrentEditorMode(p_deltaTime);
	PrepareRendering(p_deltaTime);
	UpdateEditorPanels(p_deltaTime);
	RenderViews(p_deltaTime);
	RenderEditorUI(p_deltaTime);
	m_editorActions.ExecuteDelayedActions();
}

void GeEditor::Core::Editor::HandleGlobalShortcuts()
{
	if (m_context.inputManager->IsKeyPressed(GeWindow::Inputs::EKey::KEY_DELETE) && EDITOR_EXEC(IsAnyActorSelected()) && (EDITOR_PANEL(SceneView, "Scene View").IsFocused() || EDITOR_PANEL(Hierarchy, "Hierarchy").IsFocused()))
	{
		EDITOR_EXEC(DestroyActor(EDITOR_EXEC(GetSelectedActor())));
	}
}

void GeEditor::Core::Editor::UpdateCurrentEditorMode(float p_deltaTime)
{
	if (auto editorMode = m_editorActions.GetCurrentEditorMode(); editorMode == EditorActions::EEditorMode::PLAY || editorMode == EditorActions::EEditorMode::FRAME_BY_FRAME)
		UpdatePlayMode(p_deltaTime);
	else
		UpdateEditMode(p_deltaTime);

	{
		PROFILER_SPY("Scene garbage collection");
		m_context.sceneManager.GetCurrentScene()->CollectGarbages();
		m_context.sceneManager.Update();
	}
}

void GeEditor::Core::Editor::UpdatePlayMode(float p_deltaTime)
{
	auto currentScene = m_context.sceneManager.GetCurrentScene();
	bool simulationApplied = false;

	{
		PROFILER_SPY("Physics Update");
		simulationApplied = m_context.physicsEngine->Update(p_deltaTime);
	}

	if (simulationApplied)
	{
		PROFILER_SPY("FixedUpdate");
		currentScene->FixedUpdate(p_deltaTime);
	}

	{
		PROFILER_SPY("Update");
		currentScene->Update(p_deltaTime);
	}

	{
		PROFILER_SPY("LateUpdate");
		currentScene->LateUpdate(p_deltaTime);
	}

	{
		PROFILER_SPY("Audio Update");
		m_context.audioEngine->Update();
	}

	ImGui::GetIO().DisableMouseUpdate = m_context.window->GetCursorMode() == GeWindow::Cursor::ECursorMode::DISABLED;

	if (m_editorActions.GetCurrentEditorMode() == EditorActions::EEditorMode::FRAME_BY_FRAME)
		m_editorActions.PauseGame();

	if (m_context.inputManager->IsKeyPressed(GeWindow::Inputs::EKey::KEY_ESCAPE))
		m_editorActions.StopPlaying();
}

void GeEditor::Core::Editor::UpdateEditMode(float p_deltaTime)
{
	if (m_context.inputManager->IsKeyPressed(GeWindow::Inputs::EKey::KEY_F5))
		m_editorActions.StartPlaying();
}

void GeEditor::Core::Editor::UpdateEditorPanels(float p_deltaTime)
{
	auto& menuBar = m_panelsManager.GetPanelAs<GeEditor::Panels::MenuBar>("Menu Bar");
	auto& profiler = m_panelsManager.GetPanelAs<GeEditor::Panels::Profiler>("Profiler");
	auto& hardwareInfo = m_panelsManager.GetPanelAs<GeEditor::Panels::HardwareInfo>("Hardware Info");
	auto& sceneView = m_panelsManager.GetPanelAs<GeEditor::Panels::SceneView>("Scene View");

	menuBar.HandleShortcuts(p_deltaTime);

	if (m_elapsedFrames == 1) 
		sceneView.Focus();

	if (profiler.IsOpened())
	{
		PROFILER_SPY("Profiler Update");
		profiler.Update(p_deltaTime);
	}

	if (hardwareInfo.IsOpened())
	{
		PROFILER_SPY("Hardware Info Update");
		hardwareInfo.Update(p_deltaTime);
	}
}

void GeEditor::Core::Editor::PrepareRendering(float p_deltaTime)
{
	PROFILER_SPY("Engine UBO Update");
	m_context.engineUBO->SetSubData(m_context.device->GetElapsedTime(), 3 * sizeof(GeMaths::FMatrix4) + sizeof(GeMaths::FVector3));
}

void GeEditor::Core::Editor::RenderViews(float p_deltaTime)
{
	auto& assetView = m_panelsManager.GetPanelAs<GeEditor::Panels::AssetView>("Asset View");
	auto& sceneView = m_panelsManager.GetPanelAs<GeEditor::Panels::SceneView>("Scene View");
	auto& gameView = m_panelsManager.GetPanelAs<GeEditor::Panels::GameView>("Game View");

	{
		PROFILER_SPY("Editor Views Update");

		assetView.Update(p_deltaTime);
		gameView.Update(p_deltaTime);
		sceneView.Update(p_deltaTime);
	}

	if (assetView.IsOpened())
	{
		PROFILER_SPY("Asset View Rendering");

		m_context.simulatedLightSSBO->Bind(0);
		assetView.Render();
		m_context.simulatedLightSSBO->Unbind();
	}

	m_context.lightSSBO->Bind(0);

	if (gameView.IsOpened())
	{
		PROFILER_SPY("Game View Rendering");

		gameView.Render();
	}

	if (sceneView.IsOpened())
	{
		PROFILER_SPY("Scene View Rendering");

		sceneView.Render();
	}

	m_context.lightSSBO->Unbind();
}

void GeEditor::Core::Editor::RenderEditorUI(float p_deltaTime)
{
	PROFILER_SPY("Editor UI Rendering");

	m_editorActions.GetRenderer().RenderUI();
}

void GeEditor::Core::Editor::PostUpdate()
{
	PROFILER_SPY("Editor Post-Update");

	m_context.window->SwapBuffers();
	m_context.inputManager->ClearEvents();
	++m_elapsedFrames;
}
