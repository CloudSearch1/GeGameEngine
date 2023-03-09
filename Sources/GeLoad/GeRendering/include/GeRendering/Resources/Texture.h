#pragma once

#include <stdint.h>
#include <string>

#include "GeRendering/Settings/ETextureFilteringMode.h"



namespace GeRendering::Resources
{
	namespace Loaders { class TextureLoader; }

	class Texture
	{
		friend class Loaders::TextureLoader;

	public:
    //绑定材质到给定的槽
		void Bind(uint32_t p_slot = 0) const;
		void Unbind() const;

	private:
		Texture(const std::string p_path, uint32_t p_id, uint32_t p_width, uint32_t p_height, uint32_t p_bpp, Settings::ETextureFilteringMode p_firstFilter, Settings::ETextureFilteringMode p_secondFilter, bool p_generateMipmap);
		~Texture() = default;

	public:
		const uint32_t id;
		const uint32_t width;
		const uint32_t height;
		const uint32_t bitsPerPixel;
		const Settings::ETextureFilteringMode firstFilter;
		const Settings::ETextureFilteringMode secondFilter;
		const std::string path;
		const bool isMimapped;
	};
}
