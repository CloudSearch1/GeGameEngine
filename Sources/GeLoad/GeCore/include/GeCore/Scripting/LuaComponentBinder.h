#pragma once

#include <sol.hpp>

namespace GeCore::Scripting
{
  //处理lua组件绑定
	class LuaComponentBinder
	{
	public:
    //绑定引擎组件相关的功能到lua
		static void BindComponent(sol::state& p_luaState);
	};
}
