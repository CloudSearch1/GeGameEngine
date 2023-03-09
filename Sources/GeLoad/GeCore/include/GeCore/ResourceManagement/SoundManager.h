#pragma once

#include <GeAudio/Resources/Loaders/SoundLoader.h>

#include "GeCore/ResourceManagement/AResourceManager.h"

namespace GeCore::ResourceManagement
{
  //声音资源管理器
	class SoundManager : public AResourceManager<GeAudio::Resources::Sound>
	{
	public:
    //创建给定路径标识的资源
		virtual GeAudio::Resources::Sound* CreateResource(const std::string& p_path) override;

    //销毁给定的资源
		virtual void DestroyResource(GeAudio::Resources::Sound* p_resource) override;

    //重新加载给定的资源
		virtual void ReloadResource(GeAudio::Resources::Sound* p_resource, const std::string& p_path) override;
	};
}
