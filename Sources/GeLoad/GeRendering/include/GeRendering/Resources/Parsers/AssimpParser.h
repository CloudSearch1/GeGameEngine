#include <vector>


#include "GeRendering/Geometry/Vertex.h"
#include "GeRendering/Resources/Mesh.h"
#include "GeRendering/Resources/Parsers/IModelParser.h"

#pragma once

namespace GeRendering::Resources::Parsers
{
  //加载网格模型顶点数据
	class AssimpParser : public IModelParser
	{
	public:
		
    //加载网格
		bool LoadModel
		(
			const std::string& p_fileName,
			std::vector<Mesh*>& p_meshes,
			std::vector<std::string>& p_materials,
			EModelParserFlags p_parserFlags
		) override;

	private:
		void ProcessMaterials(const struct aiScene* p_scene, std::vector<std::string>& p_materials);;
		void ProcessNode(void* p_transform, struct aiNode* p_node, const struct aiScene* p_scene, std::vector<Mesh*>& p_meshes);
		void ProcessMesh(void* p_transform, struct aiMesh* p_mesh, const struct aiScene* p_scene, std::vector<Geometry::Vertex>& p_outVertices, std::vector<uint32_t>& p_outIndices);
	};
}
