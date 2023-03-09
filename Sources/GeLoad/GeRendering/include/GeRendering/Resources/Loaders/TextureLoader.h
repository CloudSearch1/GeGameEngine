#pragma once

#include <string>
#include <vector>

#include "GeRendering/Resources/Texture.h"


namespace GeRendering::Resources::Loaders
{
  //负责纹理的创建和销毁
	class TextureLoader
	{
	public:
		TextureLoader() = delete;

    //创建纹理
		static Texture* Create(const std::string& p_filepath, GeRendering::Settings::ETextureFilteringMode p_firstFilter, GeRendering::Settings::ETextureFilteringMode p_secondFilter, bool p_generateMipmap);

    //用单一的颜色创建纹理
		static Texture* CreateColor(uint32_t p_data, GeRendering::Settings::ETextureFilteringMode p_firstFilter, GeRendering::Settings::ETextureFilteringMode p_secondFilter, bool p_generateMipmap);

    //从内存中创建纹理
		static Texture* CreateFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height, GeRendering::Settings::ETextureFilteringMode p_firstFilter, GeRendering::Settings::ETextureFilteringMode p_secondFilter, bool p_generateMipmap);

    //从文件中重新加载纹理
		static void Reload(Texture& p_texture, const std::string& p_filePath, GeRendering::Settings::ETextureFilteringMode p_firstFilter, GeRendering::Settings::ETextureFilteringMode p_secondFilter, bool p_generateMipmap);

    //销毁纹理
		static bool Destroy(Texture*& p_textureInstance);
	};
}
