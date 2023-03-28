#pragma once

#include <GeRendering/Resources/Loaders/ShaderLoader.h>

#include "GeCore/ResourceManagement/AResourceManager.h"

namespace GeCore::ResourceManagement
{
  //着色器资源管理器
	class ShaderManager : public AResourceManager<GeRendering::Resources::Shader>
	{
	public:
    //创建给定路径标识的资源
		virtual GeRendering::Resources::Shader* CreateResource(const std::string & p_path) override;

    //销毁给定的资源
		virtual void DestroyResource(GeRendering::Resources::Shader* p_resource) override;

    //重新加载给定的资源
		virtual void ReloadResource(GeRendering::Resources::Shader* p_resource, const std::string& p_path) override;
	};
}
