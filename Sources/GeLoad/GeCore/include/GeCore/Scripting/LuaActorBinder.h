#pragma once

#include <sol.hpp>

namespace GeCore::Scripting
{
  //处理actor绑定
	class LuaActorBinder
	{
	public:
    //将引擎角色相关的特性绑定到lua
		static void BindActor(sol::state& p_luaState);
	};
}
