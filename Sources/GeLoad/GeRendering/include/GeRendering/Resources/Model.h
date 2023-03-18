#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "GeRendering/Resources/Mesh.h"

namespace GeRendering::Resources
{
	namespace Loaders { class ModelLoader; }

  //模型是网格的组合
	class Model
	{
		friend class Loaders::ModelLoader;

	public:
    //返回网格
		const std::vector<Mesh*>& GetMeshes() const;

    //返回材料的名字
		const std::vector<std::string>& GetMaterialNames() const;

    //返回模型的包围球
		const GeRendering::Geometry::BoundingSphere& GetBoundingSphere() const;

	private:
		Model(const std::string& p_path);
		~Model();
    //计算包围球-Ritter方法
		void ComputeBoundingSphere();

	public:
		const std::string path;

	private:
		std::vector<Mesh*> m_meshes;
		std::vector<std::string> m_materialNames;

		Geometry::BoundingSphere m_boundingSphere;
	};
}
