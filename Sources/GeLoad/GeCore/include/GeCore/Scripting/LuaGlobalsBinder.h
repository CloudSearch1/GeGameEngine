#pragma once

#include <sol.hpp>

namespace GeCore::Scripting
{
  //处理lua全局绑定
	class LuaGlobalsBinder
	{
	public:
    //绑定引擎全局功能到lua
		static void BindGlobals(sol::state& p_luaState);
	};
}
