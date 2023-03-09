#pragma once

#include <string>

#include "GeRendering/Resources/Model.h"
#include "GeRendering/Resources/Parsers/AssimpParser.h"

namespace GeRendering::Resources::Loaders
{
  //负责模型的创建和销毁
	class ModelLoader
	{
	public:
		ModelLoader() = delete;

    //创建模型
		static Model* Create(const std::string& p_filepath, Parsers::EModelParserFlags p_parserFlags = Parsers::EModelParserFlags::NONE);

    //从文件中重新加载模型
		static void Reload(Model& p_model, const std::string& p_filePath, Parsers::EModelParserFlags p_parserFlags = Parsers::EModelParserFlags::NONE);

    //销毁一个模型
		static bool Destroy(Model*& p_modelInstance);

	private:
		static Parsers::AssimpParser __ASSIMP;
	};
}
