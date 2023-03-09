#pragma once

#include <GeUtils/Filesystem/IniFile.h>

#include <GeRendering/Buffers/UniformBuffer.h>
#include <GeRendering/Buffers/ShaderStorageBuffer.h>
#include <GeRendering/Core/ShapeDrawer.h>

#include <GePhysics/Core/PhysicsEngine.h>

#include <GeAudio/Core/AudioEngine.h>

#include <GeWindow/Context/Device.h>
#include <GeWindow/Inputs/InputManager.h>
#include <GeWindow/Window.h>

#include <GeCore/ECS/Renderer.h>
#include <GeCore/ResourceManagement/ModelManager.h>
#include <GeCore/ResourceManagement/TextureManager.h>
#include <GeCore/ResourceManagement/ShaderManager.h>
#include <GeCore/ResourceManagement/MaterialManager.h>
#include <GeCore/ResourceManagement/SoundManager.h>
#include <GeCore/SceneSystem/SceneManager.h>
#include <GeCore/Scripting/ScriptInterpreter.h>

#include <GeUI/Core/UIManager.h>
#include <GeAudio/Core/AudioEngine.h>
#include <GeAudio/Core/AudioPlayer.h>

#include "GeEditor/Core/EditorResources.h"

namespace GeEditor::Core
{
	class Context
	{
	public:
		Context(const std::string& p_projectPath, const std::string& p_projectName);

		~Context();

		void ResetProjectSettings();

		bool IsProjectSettingsIntegrityVerified();

		void ApplyProjectSettings();

	public:
		const std::string projectPath;
		const std::string projectName;
		const std::string projectFilePath;
		const std::string engineAssetsPath;
		const std::string projectAssetsPath;
		const std::string projectScriptsPath;
		const std::string editorAssetsPath;

		std::unique_ptr<GeWindow::Context::Device>			device;
		std::unique_ptr<GeWindow::Window>					window;
		std::unique_ptr<GeWindow::Inputs::InputManager>		inputManager;
		std::unique_ptr<GeRendering::Context::Driver>			driver;
		std::unique_ptr<GeCore::ECS::Renderer>					renderer;
		std::unique_ptr<GeRendering::Core::ShapeDrawer>			shapeDrawer;
		std::unique_ptr<GeUI::Core::UIManager>					uiManager;
		std::unique_ptr<GePhysics::Core::PhysicsEngine>			physicsEngine;
		std::unique_ptr<GeAudio::Core::AudioEngine>				audioEngine;
		std::unique_ptr<GeAudio::Core::AudioPlayer>				audioPlayer;
		std::unique_ptr<GeEditor::Core::EditorResources>		editorResources;

		std::unique_ptr<GeCore::Scripting::ScriptInterpreter>	scriptInterpreter;
		std::unique_ptr<GeRendering::Buffers::UniformBuffer>	engineUBO;

		std::unique_ptr<GeRendering::Buffers::ShaderStorageBuffer>	lightSSBO;
		std::unique_ptr<GeRendering::Buffers::ShaderStorageBuffer>	simulatedLightSSBO;
		
		GeCore::SceneSystem::SceneManager sceneManager;

		GeCore::ResourceManagement::ModelManager	modelManager;
		GeCore::ResourceManagement::TextureManager	textureManager;
		GeCore::ResourceManagement::ShaderManager	shaderManager;
		GeCore::ResourceManagement::MaterialManager	materialManager;
		GeCore::ResourceManagement::SoundManager	soundManager;

		GeWindow::Settings::WindowSettings windowSettings;

		GeUtils::Filesystem::IniFile projectSettings;
	};
}
