#include "GeCore/Scripting/LuaBinder.h"

#include "GeCore/Scripting/LuaMathsBinder.h"
#include "GeCore/Scripting/LuaActorBinder.h"
#include "GeCore/Scripting/LuaComponentBinder.h"
#include "GeCore/Scripting/LuaGlobalsBinder.h"

void GeCore::Scripting::LuaBinder::CallBinders(sol::state& p_luaState)
{
	auto& L = p_luaState;

	LuaMathsBinder::BindMaths(L);
	LuaActorBinder::BindActor(L);
	LuaComponentBinder::BindComponent(L);
	LuaGlobalsBinder::BindGlobals(L);
}
