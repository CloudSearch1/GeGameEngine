#pragma once

#include <GeCore/Global/ServiceLocator.h>
#include <GeUtils/Filesystem/IniFile.h>
#include <GeUtils/Utils/PathParser.h>

#include "GeEditor/Core/Context.h"
#include "GeEditor/Core/EditorRenderer.h"
#include "GeEditor/Core/PanelsManager.h"

#define EDITOR_EXEC(action)					GeCore::Global::ServiceLocator::Get<GeEditor::Core::EditorActions>().action
#define EDITOR_BIND(method, ...)			std::bind(&GeEditor::Core::EditorActions::method, &GeCore::Global::ServiceLocator::Get<GeEditor::Core::EditorActions>(), ##__VA_ARGS__)
#define EDITOR_EVENT(target)				GeCore::Global::ServiceLocator::Get<GeEditor::Core::EditorActions>().target
#define EDITOR_CONTEXT(instance)			GeCore::Global::ServiceLocator::Get<GeEditor::Core::EditorActions>().GetContext().instance
#define EDITOR_RENDERER()					GeCore::Global::ServiceLocator::Get<GeEditor::Core::EditorActions>().GetRenderer()
#define EDITOR_PANEL(type, id)				GeCore::Global::ServiceLocator::Get<GeEditor::Core::EditorActions>().GetPanelsManager().GetPanelAs<type>(id)

namespace GeEditor::Core
{
	class EditorActions
	{
	public:
		EditorActions(Context& p_context, EditorRenderer& p_editorRenderer, PanelsManager& p_panelsManager);

		#pragma region TOOLS
		Context& GetContext();

		EditorRenderer& GetRenderer();

		PanelsManager& GetPanelsManager();
		#pragma endregion

		#pragma region SETTINGS
		enum class EActorSpawnMode { ORIGIN, FRONT };

		void SetActorSpawnAtOrigin(bool p_value);

		void SetActorSpawnMode(EActorSpawnMode p_value);

		void ResetLayout();

		void SetSceneViewCameraSpeed(int p_speed);

		int GetSceneViewCameraSpeed();

		void SetAssetViewCameraSpeed(int p_speed);

		int GetAssetViewCameraSpeed();

		void ResetSceneViewCameraPosition();

		void ResetAssetViewCameraPosition();
		#pragma endregion

		#pragma region GAME
		enum class EEditorMode { EDIT, PLAY, PAUSE, FRAME_BY_FRAME };

		EEditorMode GetCurrentEditorMode() const;

		void SetEditorMode(EEditorMode p_newEditorMode);

		void StartPlaying();

		void PauseGame();

		void StopPlaying();

		void NextFrame();
		#pragma endregion

		#pragma region ACTOR_CREATION_DESTRUCTION
		template<typename T> GeCore::ECS::Actor& CreateMonoComponentActor(bool p_focusOnCreation = true, GeCore::ECS::Actor* p_parent = nullptr);

		GeMaths::FVector3 CalculateActorSpawnPoint(float p_distanceToCamera);

		GeCore::ECS::Actor&	CreateEmptyActor(bool p_focusOnCreation = true, GeCore::ECS::Actor* p_parent = nullptr, const std::string& p_name = "");

		GeCore::ECS::Actor&	CreateActorWithModel(const std::string& p_path, bool p_focusOnCreation = true, GeCore::ECS::Actor* p_parent = nullptr, const std::string& p_name = "");

		bool DestroyActor(GeCore::ECS::Actor& p_actor);

		void DuplicateActor(GeCore::ECS::Actor& p_toDuplicate, GeCore::ECS::Actor* p_forcedParent = nullptr, bool p_focus = true);
		#pragma endregion

		#pragma region ACTOR_MANIPULATION
		void SelectActor(GeCore::ECS::Actor& p_target);

		void UnselectActor();

		bool IsAnyActorSelected() const;

		GeCore::ECS::Actor&		GetSelectedActor() const;

		void MoveToTarget(GeCore::ECS::Actor& p_target);
		#pragma endregion

		#pragma region RESOURCE_MANAGEMENT
		void CompileShaders();

		void SaveMaterials();
		
		bool ImportAsset(const std::string& p_initialDestinationDirectory);

		bool ImportAssetAtLocation(const std::string& p_destination);

		std::string GetRealPath(const std::string& p_path);

		std::string GetResourcePath(const std::string& p_path, bool p_isFromEngine = false);

		std::string GetScriptPath(const std::string& p_path);

		void PropagateFolderRename(std::string p_previousName, const std::string p_newName);

		void PropagateFolderDestruction(std::string p_folderPath);

		void PropagateScriptRename(std::string p_previousName, std::string p_newName);

		void PropagateFileRename(std::string p_previousName, std::string p_newName);

		void PropagateFileRenameThroughSavedFilesOfType(const std::string& p_previousName, const std::string& p_newName, GeUtils::Utils::PathParser::EFileType p_fileType);
		#pragma endregion

		#pragma region SCENE
		void LoadEmptyScene();

		void SaveCurrentSceneTo(const std::string& p_path);

		void LoadSceneFromDisk(const std::string& p_path, bool p_absolute = false);

		bool IsCurrentSceneLoadedFromDisk() const;

		void SaveSceneChanges();

		void SaveAs();
		#pragma endregion

		#pragma region SCRIPTING
		void RefreshScripts();
		#pragma endregion

		#pragma region BUILDING
		std::optional<std::string> SelectBuildFolder();

		void Build(bool p_autoRun = false, bool p_tempFolder = false);

		void BuildAtLocation(const std::string& p_configuration, const std::string p_buildPath, bool p_autoRun = false);
		#pragma endregion

		#pragma region ACTION_SYSTEM
		void DelayAction(std::function<void()> p_action, uint32_t p_frames = 1);

		void ExecuteDelayedActions();
		#pragma endregion

	public:
		GeUtils::Eventing::Event<GeCore::ECS::Actor&> ActorSelectedEvent;
		GeUtils::Eventing::Event<GeCore::ECS::Actor&> ActorUnselectedEvent;
		GeUtils::Eventing::Event<EEditorMode> EditorModeChangedEvent;
		GeUtils::Eventing::Event<> PlayEvent;

	private:
		Context& m_context;
		PanelsManager& m_panelsManager;
		EditorRenderer& m_renderer;

		EActorSpawnMode m_actorSpawnMode = EActorSpawnMode::ORIGIN;
		EEditorMode m_editorMode = EEditorMode::EDIT;

		std::vector<std::pair<uint32_t, std::function<void()>>> m_delayedActions;

		tinyxml2::XMLDocument m_sceneBackup;
	};
}

#include "GeEditor/Core/EditorActions.inl"
