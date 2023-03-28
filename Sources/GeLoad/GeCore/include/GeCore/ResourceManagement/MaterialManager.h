#pragma once

#include "GeCore/Resources/Loaders/MaterialLoader.h"
#include "GeCore/ResourceManagement/AResourceManager.h"

namespace GeCore::ResourceManagement
{
  //材料资源管理器
	class MaterialManager : public AResourceManager<GeCore::Resources::Material>
	{
	public:
    //创建给定路径标识的资源
		virtual GeCore::Resources::Material* CreateResource(const std::string & p_path) override;

    //销毁给定的资源
		virtual void DestroyResource(GeCore::Resources::Material* p_resource) override;

    //重新加载给定的资源
		virtual void ReloadResource(GeCore::Resources::Material* p_resource, const std::string& p_path) override;
	};
}
