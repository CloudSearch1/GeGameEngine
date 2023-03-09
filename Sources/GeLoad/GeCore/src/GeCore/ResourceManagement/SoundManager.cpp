#include "GeCore/ResourceManagement/SoundManager.h"

GeAudio::Resources::Sound* GeCore::ResourceManagement::SoundManager::CreateResource(const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	GeAudio::Resources::Sound* sound = GeAudio::Resources::Loaders::SoundLoader::Create(realPath);
	if (sound)
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(sound) + offsetof(GeAudio::Resources::Sound, path)) = p_path; // Force the resource path to fit the given path

	return sound;
}

void GeCore::ResourceManagement::SoundManager::DestroyResource(GeAudio::Resources::Sound* p_resource)
{
	GeAudio::Resources::Loaders::SoundLoader::Destroy(p_resource);
}

void GeCore::ResourceManagement::SoundManager::ReloadResource(GeAudio::Resources::Sound* p_resource, const std::string& p_path)
{
}
