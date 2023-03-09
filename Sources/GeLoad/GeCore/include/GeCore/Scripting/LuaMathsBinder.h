#pragma once

#include <sol.hpp>

namespace GeCore::Scripting
{
  //处理lua数学绑定
	class LuaMathsBinder
	{
	public:
    //绑定引擎数学相关的特性到lua
		static void BindMaths(sol::state& p_luaState);
	};
}
