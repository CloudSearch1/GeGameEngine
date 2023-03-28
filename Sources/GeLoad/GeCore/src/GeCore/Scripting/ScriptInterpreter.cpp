#include <GeDebug/Logger.h>

#include "GeCore/Scripting/LuaBinder.h"
#include "GeCore/Scripting/ScriptInterpreter.h"

GeCore::Scripting::ScriptInterpreter::ScriptInterpreter(const std::string& p_scriptRootFolder) :
	m_scriptRootFolder(p_scriptRootFolder)
{
	CreateLuaContextAndBindGlobals();

	GeCore::ECS::Components::Behaviour::CreatedEvent	+= std::bind(&ScriptInterpreter::Consider, this, std::placeholders::_1);
	GeCore::ECS::Components::Behaviour::DestroyedEvent	+= std::bind(&ScriptInterpreter::Unconsider, this, std::placeholders::_1);
}

GeCore::Scripting::ScriptInterpreter::~ScriptInterpreter()
{
	DestroyLuaContext();
}

void GeCore::Scripting::ScriptInterpreter::CreateLuaContextAndBindGlobals()
{
	if (!m_luaState)
	{
		m_luaState = std::make_unique<sol::state>();
		m_luaState->open_libraries(sol::lib::base, sol::lib::math);
		GeCore::Scripting::LuaBinder::CallBinders(*m_luaState);
		m_isOk = true;

		std::for_each(m_behaviours.begin(), m_behaviours.end(), [this](ECS::Components::Behaviour* behaviour)
		{
			if (!behaviour->RegisterToLuaContext(*m_luaState, m_scriptRootFolder))
				m_isOk = false;
		});

		if (!m_isOk)
			LOG_ERROR("Script interpreter failed to register scripts. Check your lua scripts");
	}
}

void GeCore::Scripting::ScriptInterpreter::DestroyLuaContext()
{
	if (m_luaState)
	{
		std::for_each(m_behaviours.begin(), m_behaviours.end(), [this](ECS::Components::Behaviour* behaviour)
		{
			behaviour->UnregisterFromLuaContext();
		});

		m_luaState.reset();
		m_isOk = false;
	}
}

void GeCore::Scripting::ScriptInterpreter::Consider(GeCore::ECS::Components::Behaviour* p_toConsider)
{
	if (m_luaState)
	{
		m_behaviours.push_back(p_toConsider);

		if (!p_toConsider->RegisterToLuaContext(*m_luaState, m_scriptRootFolder))
			m_isOk = false;
	}
}

void GeCore::Scripting::ScriptInterpreter::Unconsider(GeCore::ECS::Components::Behaviour* p_toUnconsider)
{
	if (m_luaState)
		p_toUnconsider->UnregisterFromLuaContext();

	m_behaviours.erase(std::remove_if(m_behaviours.begin(), m_behaviours.end(), [p_toUnconsider](ECS::Components::Behaviour* behaviour)
	{
		return p_toUnconsider == behaviour;
	}));

	RefreshAll();
}

void GeCore::Scripting::ScriptInterpreter::RefreshAll()
{
	DestroyLuaContext();
	CreateLuaContextAndBindGlobals();
}

bool GeCore::Scripting::ScriptInterpreter::IsOk() const
{
	return m_isOk;
}
