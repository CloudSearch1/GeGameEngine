#pragma once

#include <vector>

#include <sol.hpp>

#include "GeCore/ECS/Components/Behaviour.h"

namespace GeCore::Scripting
{
  //处理脚本解释
	class ScriptInterpreter
	{
	public:
		ScriptInterpreter(const std::string& p_scriptRootFolder);

		~ScriptInterpreter();

    //处理lua上下文的创建，并将引擎函数绑定到lua
		void CreateLuaContextAndBindGlobals();

    //销毁lua上下文
		void DestroyLuaContext();

    //考虑行为
		void Consider(GeCore::ECS::Components::Behaviour* p_toConsider);

    //不考虑某种行为
		void Unconsider(GeCore::ECS::Components::Behaviour* p_toUnconsider);

    //刷新每个脚本
		void RefreshAll();

    //如果每个脚本都OK，则返回true
		bool IsOk() const;

	private:
		std::unique_ptr<sol::state> m_luaState;
		std::string m_scriptRootFolder;
		std::vector<GeCore::ECS::Components::Behaviour*> m_behaviours;
		bool m_isOk;
	};
}
