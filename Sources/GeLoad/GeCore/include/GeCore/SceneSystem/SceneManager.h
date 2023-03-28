#pragma once


#include "GeCore/SceneSystem/Scene.h"

namespace GeCore::SceneSystem
{
  //当前场景的场景管理器
	class SceneManager
	{
	public:

		SceneManager(const std::string& p_sceneRootFolder = "");

		~SceneManager();

		void Update();

    //加载一个延迟播放的场景
		void LoadAndPlayDelayed(const std::string& p_path, bool p_absolute = false);

    //在内存中加载一个空场景
		void LoadEmptyScene();

    //在内存中加载一个空的灯光场景
		void LoadEmptyLightedScene();

    //在内存中加载特定场景
		bool LoadScene(const std::string& p_path, bool p_absolute = false);

    //在内存中加载特定场景
		bool LoadSceneFromMemory(tinyxml2::XMLDocument& p_doc);

    //从记忆中破坏当前场景
		void UnloadCurrentScene();

    //如果场景正在加载，则返回true
		bool HasCurrentScene() const;

    //返回当前加载场景
		Scene* GetCurrentScene();

    //返回当前场景源路径
		std::string GetCurrentSceneSourcePath() const;

    //如果当前加载的场景已经从文件中加载，则返回true
		bool IsCurrentSceneLoadedFromDisk() const;

    //将给定路径存储为当前场景源路径
		void StoreCurrentSceneSourcePath(const std::string& p_path);

    //重置当前场景源路径为空字符串
		void ForgetCurrentSceneSourcePath();

	public:
		GeUtils::Eventing::Event<> SceneLoadEvent;
		GeUtils::Eventing::Event<> SceneUnloadEvent;
		GeUtils::Eventing::Event<const std::string&> CurrentSceneSourcePathChangedEvent;

	private:
		const std::string m_sceneRootFolder;
		Scene* m_currentScene = nullptr;

		bool m_currentSceneLoadedFromPath = false;
		std::string m_currentSceneSourcePath = "";

		std::function<void()> m_delayedLoadCall;
	};
}
