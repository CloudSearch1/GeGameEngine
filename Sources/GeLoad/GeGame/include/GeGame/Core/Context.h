#pragma once

#include <GeRendering/Buffers/UniformBuffer.h>
#include <GeRendering/Buffers/ShaderStorageBuffer.h>

#include <GePhysics/Core/PhysicsEngine.h>

#include <GeWindow/Context/Device.h>
#include <GeWindow/Inputs/InputManager.h>
#include <GeWindow/Window.h>

#include <GeUI/Core/UIManager.h>

#include <GeCore/ECS/Renderer.h>
#include <GeCore/ResourceManagement/ModelManager.h>
#include <GeCore/ResourceManagement/TextureManager.h>
#include <GeCore/ResourceManagement/ShaderManager.h>
#include <GeCore/ResourceManagement/MaterialManager.h>
#include <GeCore/ResourceManagement/SoundManager.h>
#include <GeCore/SceneSystem/SceneManager.h>
#include <GeCore/Scripting/ScriptInterpreter.h>

#include <GeAudio/Core/AudioEngine.h>
#include <GeAudio/Core/AudioPlayer.h>

#include <GeUtils/Filesystem/IniFile.h>

namespace GeGame::Core
{
  //上下文处理引擎功能设置
	class Context
	{
	public:
		Context();
		~Context();

	public:
		const std::string engineAssetsPath;
		const std::string projectAssetsPath;
		const std::string projectScriptsPath;

		std::unique_ptr<GeWindow::Context::Device> device;
		std::unique_ptr<GeWindow::Window> window;
		std::unique_ptr<GeWindow::Inputs::InputManager> inputManager;
		std::unique_ptr<GeRendering::Context::Driver> driver;
		std::unique_ptr<GeCore::ECS::Renderer> renderer;
		std::unique_ptr<GeUI::Core::UIManager> uiManager;
		std::unique_ptr<GePhysics::Core::PhysicsEngine> physicsEngine;
		std::unique_ptr<GeAudio::Core::AudioEngine> audioEngine;
		std::unique_ptr<GeAudio::Core::AudioPlayer> audioPlayer;
		std::unique_ptr<GeCore::Scripting::ScriptInterpreter> scriptInterpreter;
		std::unique_ptr<GeRendering::Buffers::UniformBuffer> engineUBO;
		std::unique_ptr<GeRendering::Buffers::ShaderStorageBuffer> lightSSBO;

		GeCore::SceneSystem::SceneManager sceneManager;

		GeCore::ResourceManagement::ModelManager	modelManager;
		GeCore::ResourceManagement::TextureManager	textureManager;
		GeCore::ResourceManagement::ShaderManager	shaderManager;
		GeCore::ResourceManagement::MaterialManager	materialManager;
		GeCore::ResourceManagement::SoundManager	soundManager;
		
		GeUtils::Filesystem::IniFile projectSettings;
	};
}
