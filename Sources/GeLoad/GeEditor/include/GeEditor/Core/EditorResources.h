#pragma once

#include <GeCore/ResourceManagement/TextureManager.h>
#include <GeCore/ResourceManagement/ModelManager.h>
#include <GeCore/ResourceManagement/ShaderManager.h>

namespace GeEditor::Core
{
	class EditorResources
	{
	public:
		EditorResources(const std::string& p_editorAssetsPath);

		~EditorResources();

		GeRendering::Resources::Texture* GetFileIcon(const std::string& p_filename);

		GeRendering::Resources::Texture* GetTexture(const std::string& p_id);

		GeRendering::Resources::Model* GetModel(const std::string& p_id);

		GeRendering::Resources::Shader* GetShader(const std::string& p_id);

	private:
		std::unordered_map<std::string, GeRendering::Resources::Texture*> m_textures;
		std::unordered_map<std::string, GeRendering::Resources::Model*> m_models;
		std::unordered_map<std::string, GeRendering::Resources::Shader*> m_shaders;
	};
}
