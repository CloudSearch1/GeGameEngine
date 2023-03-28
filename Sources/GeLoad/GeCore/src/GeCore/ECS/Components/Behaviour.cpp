
#include <GeUI/Widgets/Texts/TextColored.h>
#include <GeDebug/Logger.h>

#include "GeCore/ECS/Actor.h"
#include "GeCore/ECS/Components/Behaviour.h"
#include "GeCore/Scripting/LuaBinder.h"

GeUtils::Eventing::Event<GeCore::ECS::Components::Behaviour*> GeCore::ECS::Components::Behaviour::CreatedEvent;
GeUtils::Eventing::Event<GeCore::ECS::Components::Behaviour*> GeCore::ECS::Components::Behaviour::DestroyedEvent;

GeCore::ECS::Components::Behaviour::Behaviour(ECS::Actor& p_owner, const std::string& p_name) :
	name(p_name), AComponent(p_owner)
{
	CreatedEvent.Invoke(this);
}

GeCore::ECS::Components::Behaviour::~Behaviour()
{
	DestroyedEvent.Invoke(this);
}

std::string GeCore::ECS::Components::Behaviour::GetName()
{
	return "Behaviour";
}

bool GeCore::ECS::Components::Behaviour::RegisterToLuaContext(sol::state& p_luaState, const std::string& p_scriptFolder)
{
	using namespace GeCore::Scripting;

	auto result = p_luaState.safe_script_file(p_scriptFolder + name + ".lua", &sol::script_pass_on_error);

	if (!result.valid())
	{
		sol::error err = result;
		LOG_ERROR(err.what());
		return false;
	}
	else
	{
		if (result.return_count() == 1 && result[0].is<sol::table>())
		{
			m_object = result[0];
			m_object["owner"] = &owner;
			return true;
		}
		else
		{
			LOG_ERROR("'" + name + ".lua' missing return expression");
			return false;
		}
	}
}

void GeCore::ECS::Components::Behaviour::UnregisterFromLuaContext()
{
	m_object = sol::nil;
}

sol::table& GeCore::ECS::Components::Behaviour::GetTable()
{
	return m_object;
}

void GeCore::ECS::Components::Behaviour::OnAwake()
{
	LuaCall("OnAwake");
}

void GeCore::ECS::Components::Behaviour::OnStart()
{
	LuaCall("OnStart");
}

void GeCore::ECS::Components::Behaviour::OnEnable()
{
	LuaCall("OnEnable");
}

void GeCore::ECS::Components::Behaviour::OnDisable()
{
	LuaCall("OnDisable");
}

void GeCore::ECS::Components::Behaviour::OnDestroy()
{
	LuaCall("OnEnd"); 
	LuaCall("OnDestroy");
}

void GeCore::ECS::Components::Behaviour::OnUpdate(float p_deltaTime)
{
	LuaCall("OnUpdate", p_deltaTime);
}

void GeCore::ECS::Components::Behaviour::OnFixedUpdate(float p_deltaTime)
{
	LuaCall("OnFixedUpdate", p_deltaTime);
}

void GeCore::ECS::Components::Behaviour::OnLateUpdate(float p_deltaTime)
{
	LuaCall("OnLateUpdate", p_deltaTime);
}

void GeCore::ECS::Components::Behaviour::OnCollisionEnter(Components::CPhysicalObject& p_otherObject)
{
	LuaCall("OnCollisionStart", p_otherObject); 
	LuaCall("OnCollisionEnter", p_otherObject);
}

void GeCore::ECS::Components::Behaviour::OnCollisionStay(Components::CPhysicalObject& p_otherObject)
{
	LuaCall("OnCollisionStay", p_otherObject);
}

void GeCore::ECS::Components::Behaviour::OnCollisionExit(Components::CPhysicalObject& p_otherObject)
{
	LuaCall("OnCollisionStop", p_otherObject); 
	LuaCall("OnCollisionExit", p_otherObject);
}

void GeCore::ECS::Components::Behaviour::OnTriggerEnter(Components::CPhysicalObject& p_otherObject)
{
	LuaCall("OnTriggerStart", p_otherObject); 
	LuaCall("OnTriggerEnter", p_otherObject);
}

void GeCore::ECS::Components::Behaviour::OnTriggerStay(Components::CPhysicalObject& p_otherObject)
{
	LuaCall("OnTriggerStay", p_otherObject);
}

void GeCore::ECS::Components::Behaviour::OnTriggerExit(Components::CPhysicalObject& p_otherObject)
{
	LuaCall("OnTriggerStop", p_otherObject); 
	LuaCall("OnTriggerExit", p_otherObject);
}

void GeCore::ECS::Components::Behaviour::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
}

void GeCore::ECS::Components::Behaviour::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
}

void GeCore::ECS::Components::Behaviour::OnInspector(GeUI::Internal::WidgetContainer & p_root)
{
	using namespace GeMaths;
	using namespace GeCore::Helpers;

	if (m_object.valid())
	{
		p_root.CreateWidget<GeUI::Widgets::Texts::TextColored>("Ready", GeUI::Types::Color::Green);
		p_root.CreateWidget<GeUI::Widgets::Texts::TextColored>("Your script gets interpreted by the engine with success", GeUI::Types::Color::White);
	}
	else
	{
		p_root.CreateWidget<GeUI::Widgets::Texts::TextColored>("Compilation failed!", GeUI::Types::Color::Red);
		p_root.CreateWidget<GeUI::Widgets::Texts::TextColored>("Check the console for more information", GeUI::Types::Color::White);
	}
}
