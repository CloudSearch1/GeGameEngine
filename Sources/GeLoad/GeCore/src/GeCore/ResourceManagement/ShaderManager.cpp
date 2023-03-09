#include "GeCore/ResourceManagement/ShaderManager.h"

GeRendering::Resources::Shader* GeCore::ResourceManagement::ShaderManager::CreateResource(const std::string & p_path)
{
	std::string realPath = GetRealPath(p_path);
	GeRendering::Resources::Shader* shader = GeRendering::Resources::Loaders::ShaderLoader::Create(realPath);
	if (shader)
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(shader) + offsetof(GeRendering::Resources::Shader, path)) = p_path; // Force the resource path to fit the given path

	return shader;
}

void GeCore::ResourceManagement::ShaderManager::DestroyResource(GeRendering::Resources::Shader* p_resource)
{
	GeRendering::Resources::Loaders::ShaderLoader::Destroy(p_resource);
}

void GeCore::ResourceManagement::ShaderManager::ReloadResource(GeRendering::Resources::Shader* p_resource, const std::string& p_path)
{
	GeRendering::Resources::Loaders::ShaderLoader::Recompile(*p_resource, p_path);
}
