#pragma once

#include <GeRendering/Resources/Loaders/ModelLoader.h>

#include "GeCore/ResourceManagement/AResourceManager.h"

namespace GeCore::ResourceManagement
{
  //模型资源管理器
	class ModelManager : public AResourceManager<GeRendering::Resources::Model>
	{
	public:
    //创建给定路径标识的资源
		virtual GeRendering::Resources::Model* CreateResource(const std::string & p_path) override;

    //销毁给定的资源
		virtual void DestroyResource(GeRendering::Resources::Model* p_resource) override;

    //重新加载给定的资源
		virtual void ReloadResource(GeRendering::Resources::Model* p_resource, const std::string& p_path) override;
	};
}
