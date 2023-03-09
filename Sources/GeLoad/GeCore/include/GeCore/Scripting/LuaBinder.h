#pragma once

#include <sol.hpp>

namespace GeCore::Scripting
{
  //处理lua绑定
	class LuaBinder
	{
	public:
    //绑定引擎功能到lua
		static void CallBinders(sol::state& p_luaState);
	};
}
