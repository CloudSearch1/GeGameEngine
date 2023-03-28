#pragma once

#include "GeCore/Resources/Material.h"

namespace GeCore::Resources::Loaders
{
  //处理材料的创建
	class MaterialLoader
	{
	public:
		MaterialLoader() = delete;

    //从文件实例化材质
		static Material* Create(const std::string & p_path);

    //使用给定的文件路径重新加载材料
		static void Reload(Material& p_material, const std::string& p_path);

    //将素材保存到给定路径
		static void Save(Material& p_material, const std::string& p_path);

    //销毁给定的材料
		static bool Destroy(Material*& p_material);
	};
}
