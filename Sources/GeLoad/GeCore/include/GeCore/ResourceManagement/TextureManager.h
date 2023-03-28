#pragma once

#include <GeRendering/Resources/Loaders/TextureLoader.h>

#include "GeCore/ResourceManagement/AResourceManager.h"

namespace GeCore::ResourceManagement
{
  //纹理资源管理器
	class TextureManager : public AResourceManager<GeRendering::Resources::Texture>
	{
	public:
    //创建给定路径标识的资源
		virtual GeRendering::Resources::Texture* CreateResource(const std::string & p_path) override;

    //销毁给定的资源
		virtual void DestroyResource(GeRendering::Resources::Texture* p_resource) override;

    //重新加载给定的资源
		virtual void ReloadResource(GeRendering::Resources::Texture* p_resource, const std::string& p_path) override;
	};
}
