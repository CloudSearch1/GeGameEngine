#include "GeCore/ResourceManagement/TextureManager.h"
#include "GeRendering/Settings/DriverSettings.h"

#include <GeUtils/Filesystem/IniFile.h>

std::tuple<GeRendering::Settings::ETextureFilteringMode, GeRendering::Settings::ETextureFilteringMode, bool> GetAssetMetadata(const std::string& p_path)
{
	auto metaFile = GeUtils::Filesystem::IniFile(p_path + ".meta");

	auto min = metaFile.GetOrDefault("MIN_FILTER", static_cast<int>(GeRendering::Settings::ETextureFilteringMode::LINEAR_MIPMAP_LINEAR));
	auto mag = metaFile.GetOrDefault("MAG_FILTER", static_cast<int>(GeRendering::Settings::ETextureFilteringMode::LINEAR));
	auto mipmap = metaFile.GetOrDefault("ENABLE_MIPMAPPING", true);

	return { static_cast<GeRendering::Settings::ETextureFilteringMode>(min), static_cast<GeRendering::Settings::ETextureFilteringMode>(mag), mipmap };
}

GeRendering::Resources::Texture* GeCore::ResourceManagement::TextureManager::CreateResource(const std::string & p_path)
{
	std::string realPath = GetRealPath(p_path);

	auto [min, mag, mipmap] = GetAssetMetadata(realPath);

	GeRendering::Resources::Texture* texture = GeRendering::Resources::Loaders::TextureLoader::Create(realPath, min, mag, mipmap);
	if (texture)
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(texture) + offsetof(GeRendering::Resources::Texture, path)) = p_path; // Force the resource path to fit the given path

	return texture;
}

void GeCore::ResourceManagement::TextureManager::DestroyResource(GeRendering::Resources::Texture* p_resource)
{
	GeRendering::Resources::Loaders::TextureLoader::Destroy(p_resource);
}

void GeCore::ResourceManagement::TextureManager::ReloadResource(GeRendering::Resources::Texture* p_resource, const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);

	auto [min, mag, mipmap] = GetAssetMetadata(realPath);

	GeRendering::Resources::Loaders::TextureLoader::Reload(*p_resource, realPath, min, mag, mipmap);
}
