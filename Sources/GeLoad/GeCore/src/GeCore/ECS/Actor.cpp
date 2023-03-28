#include <algorithm>

#include "GeCore/ECS/Actor.h"

#include "GeCore/ECS/Components/CPhysicalBox.h"
#include "GeCore/ECS/Components/CPhysicalSphere.h"
#include "GeCore/ECS/Components/CPhysicalCapsule.h"
#include "GeCore/ECS/Components/CCamera.h"
#include "GeCore/ECS/Components/CModelRenderer.h"
#include "GeCore/ECS/Components/CMaterialRenderer.h"
#include "GeCore/ECS/Components/CAudioSource.h"
#include "GeCore/ECS/Components/CAudioListener.h"
#include "GeCore/ECS/Components/CPointLight.h"
#include "GeCore/ECS/Components/CDirectionalLight.h"
#include "GeCore/ECS/Components/CSpotLight.h"
#include "GeCore/ECS/Components/CAmbientBoxLight.h"
#include "GeCore/ECS/Components/CAmbientSphereLight.h"

GeUtils::Eventing::Event<GeCore::ECS::Actor&> GeCore::ECS::Actor::DestroyedEvent;
GeUtils::Eventing::Event<GeCore::ECS::Actor&> GeCore::ECS::Actor::CreatedEvent;
GeUtils::Eventing::Event<GeCore::ECS::Actor&, GeCore::ECS::Actor&> GeCore::ECS::Actor::AttachEvent;
GeUtils::Eventing::Event<GeCore::ECS::Actor&> GeCore::ECS::Actor::DettachEvent;

GeCore::ECS::Actor::Actor(int64_t p_actorID, const std::string & p_name, const std::string & p_tag, bool& p_playing) :
	m_actorID(p_actorID),
	m_name(p_name),
	m_tag(p_tag),
	m_playing(p_playing),
	transform(AddComponent<Components::CTransform>())
{
	CreatedEvent.Invoke(*this);
}

GeCore::ECS::Actor::~Actor()
{
	if (!m_sleeping)
	{
		if (IsActive())
			OnDisable();

		if (m_awaked && m_started)
			OnDestroy();
	}

	DestroyedEvent.Invoke(*this);

	std::vector<Actor*> toDetach = m_children;

	for (auto child : toDetach)
		child->DetachFromParent();

	toDetach.clear();

	DetachFromParent();

	std::for_each(m_components.begin(), m_components.end(), [&](std::shared_ptr<Components::AComponent> p_component) { ComponentRemovedEvent.Invoke(*p_component); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto& p_behaviour) { BehaviourRemovedEvent.Invoke(std::ref(p_behaviour.second)); });
	std::for_each(m_children.begin(), m_children.end(),		[](Actor* p_element) { delete p_element; });
}

const std::string & GeCore::ECS::Actor::GetName() const
{
	return m_name;
}

const std::string & GeCore::ECS::Actor::GetTag() const
{
	return m_tag;
}

void GeCore::ECS::Actor::SetName(const std::string & p_name)
{
	m_name = p_name;
}

void GeCore::ECS::Actor::SetTag(const std::string & p_tag)
{
	m_tag = p_tag;
}

void GeCore::ECS::Actor::SetActive(bool p_active)
{
	if (p_active != m_active)
	{
		RecursiveWasActiveUpdate();
		m_active = p_active;
		RecursiveActiveUpdate();
	}
}

bool GeCore::ECS::Actor::IsSelfActive() const
{
	return m_active;
}

bool GeCore::ECS::Actor::IsActive() const
{
	return m_active && (m_parent ? m_parent->IsActive() : true);
}

void GeCore::ECS::Actor::SetID(int64_t p_id)
{
	m_actorID = p_id;
}

int64_t GeCore::ECS::Actor::GetID() const
{
	return m_actorID;
}

void GeCore::ECS::Actor::SetParent(Actor& p_parent)
{
	DetachFromParent();

	m_parent = &p_parent;
	m_parentID = p_parent.m_actorID;
	transform.SetParent(p_parent.transform);

	p_parent.m_children.push_back(this);

	AttachEvent.Invoke(*this, p_parent);
}

void GeCore::ECS::Actor::DetachFromParent()
{
	DettachEvent.Invoke(*this);

	if (m_parent)
	{
		m_parent->m_children.erase(std::remove_if(m_parent->m_children.begin(), m_parent->m_children.end(), [this](Actor* p_element)
		{
			return p_element == this;
		}));
	}

	m_parent = nullptr;
	m_parentID = 0;

	transform.RemoveParent();
}

bool GeCore::ECS::Actor::HasParent() const
{
	return m_parent;
}

GeCore::ECS::Actor * GeCore::ECS::Actor::GetParent() const
{
	return m_parent;
}

int64_t GeCore::ECS::Actor::GetParentID() const
{
	return m_parentID;
}

std::vector<GeCore::ECS::Actor*>& GeCore::ECS::Actor::GetChildren()
{
	return m_children;
}

void GeCore::ECS::Actor::MarkAsDestroy()
{
	m_destroyed = true;

	for (auto child : m_children)
		child->MarkAsDestroy();
}

bool GeCore::ECS::Actor::IsAlive() const
{
	return !m_destroyed;
}

void GeCore::ECS::Actor::SetSleeping(bool p_sleeping)
{
	m_sleeping = p_sleeping;
}

void GeCore::ECS::Actor::OnAwake()
{
	m_awaked = true;
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnAwake(); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [](auto & element) { element.second.OnAwake(); });
}

void GeCore::ECS::Actor::OnStart()
{
	m_started = true;
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnStart(); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [](auto & element) { element.second.OnStart(); });
}

void GeCore::ECS::Actor::OnEnable()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnEnable(); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [](auto & element) { element.second.OnEnable(); });
}

void GeCore::ECS::Actor::OnDisable()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnDisable(); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [](auto & element) { element.second.OnDisable(); });
}

void GeCore::ECS::Actor::OnDestroy()
{
	std::for_each(m_components.begin(), m_components.end(), [](auto element) { element->OnDestroy(); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [](auto & element) { element.second.OnDestroy(); });
}

void GeCore::ECS::Actor::OnUpdate(float p_deltaTime)
{
	if (IsActive())
	{
		std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnUpdate(p_deltaTime); });
		std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnUpdate(p_deltaTime); });
	}
}

void GeCore::ECS::Actor::OnFixedUpdate(float p_deltaTime)
{
	if (IsActive())
	{
		std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnFixedUpdate(p_deltaTime); });
		std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnFixedUpdate(p_deltaTime); });
	}
}

void GeCore::ECS::Actor::OnLateUpdate(float p_deltaTime)
{
	if (IsActive())
	{
		std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnLateUpdate(p_deltaTime); });
		std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnLateUpdate(p_deltaTime); });
	}
}

void GeCore::ECS::Actor::OnCollisionEnter(Components::CPhysicalObject& p_otherObject)
{
	std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnCollisionEnter(p_otherObject); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnCollisionEnter(p_otherObject); });
}

void GeCore::ECS::Actor::OnCollisionStay(Components::CPhysicalObject& p_otherObject)
{
	std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnCollisionStay(p_otherObject); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnCollisionStay(p_otherObject); });
}

void GeCore::ECS::Actor::OnCollisionExit(Components::CPhysicalObject& p_otherObject)
{
	std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnCollisionExit(p_otherObject); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnCollisionExit(p_otherObject); });
}

void GeCore::ECS::Actor::OnTriggerEnter(Components::CPhysicalObject& p_otherObject)
{
	std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnTriggerEnter(p_otherObject); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnTriggerEnter(p_otherObject); });
}

void GeCore::ECS::Actor::OnTriggerStay(Components::CPhysicalObject& p_otherObject)
{
	std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnTriggerStay(p_otherObject); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnTriggerStay(p_otherObject); });
}

void GeCore::ECS::Actor::OnTriggerExit(Components::CPhysicalObject& p_otherObject)
{
	std::for_each(m_components.begin(), m_components.end(), [&](auto element) { element->OnTriggerExit(p_otherObject); });
	std::for_each(m_behaviours.begin(), m_behaviours.end(), [&](auto & element) { element.second.OnTriggerExit(p_otherObject); });
}

bool GeCore::ECS::Actor::RemoveComponent(GeCore::ECS::Components::AComponent& p_component)
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		if (it->get() == &p_component)
		{
			ComponentRemovedEvent.Invoke(p_component);
			m_components.erase(it);
			return true;
		}
	}

	return false;
}

std::vector<std::shared_ptr<GeCore::ECS::Components::AComponent>>& GeCore::ECS::Actor::GetComponents()
{
	return m_components;
}

GeCore::ECS::Components::Behaviour & GeCore::ECS::Actor::AddBehaviour(const std::string & p_name)
{
	m_behaviours.try_emplace(p_name, *this, p_name);
	Components::Behaviour& newInstance = m_behaviours.at(p_name);
	BehaviourAddedEvent.Invoke(newInstance);
	if (m_playing && IsActive())
	{
		newInstance.OnAwake();
		newInstance.OnEnable();
		newInstance.OnStart();
	}
	return newInstance;
}

bool GeCore::ECS::Actor::RemoveBehaviour(Components::Behaviour& p_behaviour)
{
	bool found = false;

	for (auto& [name, behaviour] : m_behaviours)
	{
		if (&behaviour == &p_behaviour)
		{
			found = true;
			break;
		}
	}

	if (found)
		return RemoveBehaviour(p_behaviour.name);
	else
		return false;
}

bool GeCore::ECS::Actor::RemoveBehaviour(const std::string & p_name)
{
	Components::Behaviour* found = GetBehaviour(p_name);
	if (found)
	{
		BehaviourRemovedEvent.Invoke(*found);
		return m_behaviours.erase(p_name);
	}
	else
	{
		return false;
	}
}

GeCore::ECS::Components::Behaviour* GeCore::ECS::Actor::GetBehaviour(const std::string& p_name)
{
	if (auto result = m_behaviours.find(p_name); result != m_behaviours.end())
		return &result->second;
	else
		return nullptr;
}

std::unordered_map<std::string, GeCore::ECS::Components::Behaviour>& GeCore::ECS::Actor::GetBehaviours()
{
	return m_behaviours;
}

void GeCore::ECS::Actor::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_actorsRoot)
{
	tinyxml2::XMLNode* actorNode = p_doc.NewElement("actor");
	p_actorsRoot->InsertEndChild(actorNode);

	GeCore::Helpers::Serializer::SerializeString(p_doc, actorNode, "name", m_name);
	GeCore::Helpers::Serializer::SerializeString(p_doc, actorNode, "tag", m_tag);
	GeCore::Helpers::Serializer::SerializeBoolean(p_doc, actorNode, "active", m_active);
	GeCore::Helpers::Serializer::SerializeInt64(p_doc, actorNode, "id", m_actorID);
	GeCore::Helpers::Serializer::SerializeInt64(p_doc, actorNode, "parent", m_parentID);

	tinyxml2::XMLNode* componentsNode = p_doc.NewElement("components");
	actorNode->InsertEndChild(componentsNode);

	for (auto& component : m_components)
	{
		tinyxml2::XMLNode* componentNode = p_doc.NewElement("component");
		componentsNode->InsertEndChild(componentNode);

		GeCore::Helpers::Serializer::SerializeString(p_doc, componentNode, "type", typeid(*component).name());

		tinyxml2::XMLElement* data = p_doc.NewElement("data");
		componentNode->InsertEndChild(data);

		component->OnSerialize(p_doc, data);
	}

	tinyxml2::XMLNode* behavioursNode = p_doc.NewElement("behaviours");
	actorNode->InsertEndChild(behavioursNode);

	for (auto& behaviour : m_behaviours)
	{
		tinyxml2::XMLNode* behaviourNode = p_doc.NewElement("behaviour");
		behavioursNode->InsertEndChild(behaviourNode);

		GeCore::Helpers::Serializer::SerializeString(p_doc, behaviourNode, "type", behaviour.first);

		tinyxml2::XMLElement* data = p_doc.NewElement("data");
		behaviourNode->InsertEndChild(data);

		behaviour.second.OnSerialize(p_doc, data);
	}
}

void GeCore::ECS::Actor::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_actorsRoot)
{
	GeCore::Helpers::Serializer::DeserializeString(p_doc, p_actorsRoot, "name", m_name);
	GeCore::Helpers::Serializer::DeserializeString(p_doc, p_actorsRoot, "tag", m_tag);
	GeCore::Helpers::Serializer::DeserializeBoolean(p_doc, p_actorsRoot, "active", m_active);
	GeCore::Helpers::Serializer::DeserializeInt64(p_doc, p_actorsRoot, "id", m_actorID);
	GeCore::Helpers::Serializer::DeserializeInt64(p_doc, p_actorsRoot, "parent", m_parentID);

	{
		tinyxml2::XMLNode* componentsRoot = p_actorsRoot->FirstChildElement("components");
		if (componentsRoot)
		{
			tinyxml2::XMLElement* currentComponent = componentsRoot->FirstChildElement("component");

			while (currentComponent)
			{
				std::string componentType = currentComponent->FirstChildElement("type")->GetText();
				GeCore::ECS::Components::AComponent* component = nullptr;

				if (componentType == typeid(Components::CTransform).name())			component = &transform;
				else if (componentType == typeid(Components::CPhysicalBox).name())			component = &AddComponent<GeCore::ECS::Components::CPhysicalBox>();
				else if (componentType == typeid(Components::CPhysicalSphere).name())		component = &AddComponent<GeCore::ECS::Components::CPhysicalSphere>();
				else if (componentType == typeid(Components::CPhysicalCapsule).name())		component = &AddComponent<GeCore::ECS::Components::CPhysicalCapsule>();
				else if (componentType == typeid(Components::CModelRenderer).name())			component = &AddComponent<GeCore::ECS::Components::CModelRenderer>();
				else if (componentType == typeid(Components::CCamera).name())				component = &AddComponent<GeCore::ECS::Components::CCamera>();
				else if (componentType == typeid(Components::CMaterialRenderer).name())		component = &AddComponent<GeCore::ECS::Components::CMaterialRenderer>();
				else if (componentType == typeid(Components::CAudioSource).name())			component = &AddComponent<GeCore::ECS::Components::CAudioSource>();
				else if (componentType == typeid(Components::CAudioListener).name())		component = &AddComponent<GeCore::ECS::Components::CAudioListener>();
				else if (componentType == typeid(Components::CPointLight).name())			component = &AddComponent<GeCore::ECS::Components::CPointLight>();
				else if (componentType == typeid(Components::CDirectionalLight).name())		component = &AddComponent<GeCore::ECS::Components::CDirectionalLight>();
				else if (componentType == typeid(Components::CSpotLight).name())			component = &AddComponent<GeCore::ECS::Components::CSpotLight>();
				else if (componentType == typeid(Components::CAmbientBoxLight).name())		component = &AddComponent<GeCore::ECS::Components::CAmbientBoxLight>();
				else if (componentType == typeid(Components::CAmbientSphereLight).name())	component = &AddComponent<GeCore::ECS::Components::CAmbientSphereLight>();

				if (component)
					component->OnDeserialize(p_doc, currentComponent->FirstChildElement("data"));

				currentComponent = currentComponent->NextSiblingElement("component");
			}
		}
	}

	{
		tinyxml2::XMLNode* behavioursRoot = p_actorsRoot->FirstChildElement("behaviours");

		if (behavioursRoot)
		{
			tinyxml2::XMLElement* currentBehaviour = behavioursRoot->FirstChildElement("behaviour");

			while (currentBehaviour)
			{
				std::string behaviourType = currentBehaviour->FirstChildElement("type")->GetText();

				auto& behaviour = AddBehaviour(behaviourType);
				behaviour.OnDeserialize(p_doc, currentBehaviour->FirstChildElement("data"));

				currentBehaviour = currentBehaviour->NextSiblingElement("behaviour");
			}
		}
	}
}

void GeCore::ECS::Actor::RecursiveActiveUpdate()
{
	bool isActive = IsActive();

	if (!m_sleeping)
	{
		if (!m_wasActive && isActive)
		{
			if (!m_awaked)
				OnAwake();

			OnEnable();

			if (!m_started)
				OnStart();
		}

		if (m_wasActive && !isActive)
			OnDisable();
	}

	for (auto child : m_children)
		child->RecursiveActiveUpdate();
}

void GeCore::ECS::Actor::RecursiveWasActiveUpdate()
{
	m_wasActive = IsActive();
	for (auto child : m_children)
		child->RecursiveWasActiveUpdate();
}
