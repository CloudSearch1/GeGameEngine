#pragma once

#include <string>
#include <any>

#include "GeRendering/Resources/UniformType.h"

namespace GeRendering::Resources
{
  //Uniform数据结构
	struct UniformInfo
	{
		UniformType		type;
		std::string		name;
		uint32_t		  location;
		std::any		  defaultValue;
	};
}
