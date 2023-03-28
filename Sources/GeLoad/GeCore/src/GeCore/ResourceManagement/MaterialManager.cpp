#include "GeCore/ResourceManagement/MaterialManager.h"

GeCore::Resources::Material * GeCore::ResourceManagement::MaterialManager::CreateResource(const std::string & p_path)
{
	std::string realPath = GetRealPath(p_path);

	Resources::Material* material = GeCore::Resources::Loaders::MaterialLoader::Create(realPath);
	if (material)
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(material) + offsetof(Resources::Material, path)) = p_path; // Force the resource path to fit the given path
	}

	return material;
}

void GeCore::ResourceManagement::MaterialManager::DestroyResource(GeCore::Resources::Material * p_resource)
{
	GeCore::Resources::Loaders::MaterialLoader::Destroy(p_resource);
}

void GeCore::ResourceManagement::MaterialManager::ReloadResource(GeCore::Resources::Material* p_resource, const std::string& p_path)
{
	GeCore::Resources::Loaders::MaterialLoader::Reload(*p_resource, p_path);
}
