#pragma once

#include <unordered_map>
#include <any>


namespace GeCore::ResourceManagement
{
  //处理各种变量类型资源的管理
	template<typename T>
	class AResourceManager
	{
	public:
    //处理资源的创建并注册
		T* LoadResource(const std::string& p_path);

    //处理资源的销毁并取消注册
		void UnloadResource(const std::string& p_path);

    //将资源移动到新给定的 id（路径）
		bool MoveResource(const std::string& p_previousPath, const std::string& p_newPath);

    //重新加载资源
		void ReloadResource(const std::string& p_path);

    //如果资源存在则返回 true（= 已注册）
		bool IsResourceRegistered(const std::string& p_path);

    //销毁和注销所有资源
		void UnloadResources();

    //注册资源并将其与给定路径相关联。
		T* RegisterResource(const std::string& p_path, T* p_instance);

    //注销资源（调用此方法之前必须销毁资源
		void UnregisterResource(const std::string& p_path);

    //返回链接到给定路径的实例，如果未注册则尝试加载它。
		T* GetResource(const std::string& p_path, bool p_tryToLoadIfNotFound = true);

    //运算符重载以获取链接到给定路径的实例。
		T* operator[](const std::string& p_path);

    //为资源管理器提供资产路径
		static void ProvideAssetPaths(const std::string& p_projectAssetsPath, const std::string& p_engineAssetsPath);

    //返回资源图
		std::unordered_map<std::string, T*>& GetResources();

	protected:
		virtual T* CreateResource(const std::string& p_path) = 0;
		virtual void DestroyResource(T* p_resource) = 0;
		virtual void ReloadResource(T* p_resource, const std::string& p_path) = 0;
		std::string GetRealPath(const std::string& p_path) const;

	private:
		inline static std::string __PROJECT_ASSETS_PATH = "";
		inline static std::string __ENGINE_ASSETS_PATH = "";

		std::unordered_map<std::string, T*> m_resources;
	};
}

#include "GeCore/ResourceManagement/AResourceManager.inl"
