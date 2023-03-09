#pragma once

#include <string>

#include "GeRendering/Resources/Mesh.h"
#include "GeRendering/Resources/Parsers/EModelParserFlags.h"

namespace GeRendering::Resources::Parsers
{
  //模型解析器接口
	class IModelParser
	{
	public:
		
    //加载网格
		virtual bool LoadModel
		(
			const std::string& p_fileName,
			std::vector<Mesh*>& p_meshes,
			std::vector<std::string>& p_materials,
			EModelParserFlags p_parserFlags
		) = 0;
	};
}
