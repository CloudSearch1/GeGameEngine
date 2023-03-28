#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Selection/ComboBox.h>

#include <GeDebug/Logger.h>

#include <GePhysics/Entities/PhysicalObject.h>

#include "GeCore/ECS/Components/CPhysicalObject.h"
#include "GeCore/ECS/Actor.h"

GeCore::ECS::Components::CPhysicalObject::CPhysicalObject(ECS::Actor & p_owner) : 
	AComponent(p_owner)
{
}

void GeCore::ECS::Components::CPhysicalObject::AddForce(const GeMaths::FVector3 & p_force)
{
	m_physicalObject->AddForce(p_force);
}

void GeCore::ECS::Components::CPhysicalObject::AddImpulse(const GeMaths::FVector3 & p_impulse)
{
	m_physicalObject->AddImpulse(p_impulse);
}

void GeCore::ECS::Components::CPhysicalObject::ClearForces()
{
	m_physicalObject->ClearForces();
}

void GeCore::ECS::Components::CPhysicalObject::SetCollisionDetectionMode(GePhysics::Entities::PhysicalObject::ECollisionDetectionMode p_mode)
{
	m_physicalObject->SetCollisionDetectionMode(p_mode);
}

GePhysics::Entities::PhysicalObject::ECollisionDetectionMode GeCore::ECS::Components::CPhysicalObject::GetCollisionDetectionMode() const
{
	return m_physicalObject->GetCollisionDetectionMode();
}

float GeCore::ECS::Components::CPhysicalObject::GetMass() const
{
	return m_physicalObject->GetMass();
}

float GeCore::ECS::Components::CPhysicalObject::GetBounciness() const
{
	return m_physicalObject->GetBounciness();
}

float GeCore::ECS::Components::CPhysicalObject::GetFriction() const
{
	return m_physicalObject->GetFriction();
}

GeMaths::FVector3 GeCore::ECS::Components::CPhysicalObject::GetLinearVelocity() const
{
	return m_physicalObject->GetLinearVelocity();
}

GeMaths::FVector3 GeCore::ECS::Components::CPhysicalObject::GetAngularVelocity() const
{
	return m_physicalObject->GetAngularVelocity();
}

GeMaths::FVector3 GeCore::ECS::Components::CPhysicalObject::GetLinearFactor() const
{
	return m_physicalObject->GetLinearFactor();
}

GeMaths::FVector3 GeCore::ECS::Components::CPhysicalObject::GetAngularFactor() const
{
	return m_physicalObject->GetAngularFactor();
}

bool GeCore::ECS::Components::CPhysicalObject::IsTrigger() const
{
	return m_physicalObject->IsTrigger();
}

bool GeCore::ECS::Components::CPhysicalObject::IsKinematic() const
{
	return m_physicalObject->IsKinematic();
}

GePhysics::Entities::PhysicalObject::EActivationState GeCore::ECS::Components::CPhysicalObject::GetActivationState() const
{
	return m_physicalObject->GetActivationState();
}

void GeCore::ECS::Components::CPhysicalObject::SetMass(float p_mass)
{
	m_physicalObject->SetMass(p_mass);
}

void GeCore::ECS::Components::CPhysicalObject::SetBounciness(float p_bounciness)
{
	m_physicalObject->SetBounciness(p_bounciness);
}

void GeCore::ECS::Components::CPhysicalObject::SetFriction(float p_friction)
{
	m_physicalObject->SetFriction(p_friction);
}

void GeCore::ECS::Components::CPhysicalObject::SetLinearVelocity(const GeMaths::FVector3 & p_linearVelocity)
{
	m_physicalObject->SetLinearVelocity(p_linearVelocity);
}

void GeCore::ECS::Components::CPhysicalObject::SetAngularVelocity(const GeMaths::FVector3 & p_angularVelocity)
{
	m_physicalObject->SetAngularVelocity(p_angularVelocity);
}

void GeCore::ECS::Components::CPhysicalObject::SetLinearFactor(const GeMaths::FVector3 & p_linearFactor)
{
	m_physicalObject->SetLinearFactor(p_linearFactor);
}

void GeCore::ECS::Components::CPhysicalObject::SetAngularFactor(const GeMaths::FVector3 & p_angularFactor)
{
	m_physicalObject->SetAngularFactor(p_angularFactor);
}

void GeCore::ECS::Components::CPhysicalObject::SetTrigger(bool p_trigger)
{
	m_physicalObject->SetTrigger(p_trigger);
}

void GeCore::ECS::Components::CPhysicalObject::SetKinematic(bool p_kinematic)
{
	m_physicalObject->SetKinematic(p_kinematic);
}

void GeCore::ECS::Components::CPhysicalObject::SetActivationState(GePhysics::Entities::PhysicalObject::EActivationState p_state)
{
	m_physicalObject->SetActivationState(p_state);
}

void GeCore::ECS::Components::CPhysicalObject::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	Helpers::Serializer::SerializeBoolean(p_doc, p_node, "is_trigger", IsTrigger());
	Helpers::Serializer::SerializeBoolean(p_doc, p_node, "is_kinematic", IsKinematic());
	Helpers::Serializer::SerializeFloat(p_doc, p_node, "bounciness", GetBounciness());
	Helpers::Serializer::SerializeFloat(p_doc, p_node, "mass", GetMass());
	Helpers::Serializer::SerializeFloat(p_doc, p_node, "friction", GetFriction());
	Helpers::Serializer::SerializeVec3(p_doc, p_node, "linear_factor", GetLinearFactor());
	Helpers::Serializer::SerializeVec3(p_doc, p_node, "angular_factor", GetAngularFactor());
	Helpers::Serializer::SerializeInt(p_doc, p_node, "collision_mode", static_cast<int>(GetCollisionDetectionMode()));
}

void GeCore::ECS::Components::CPhysicalObject::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	SetTrigger(Helpers::Serializer::DeserializeBoolean(p_doc, p_node, "is_trigger"));
	SetKinematic(Helpers::Serializer::DeserializeBoolean(p_doc, p_node, "is_kinematic"));
	SetBounciness(Helpers::Serializer::DeserializeFloat(p_doc, p_node, "bounciness"));
	SetMass(Helpers::Serializer::DeserializeFloat(p_doc, p_node, "mass"));
	SetFriction(Helpers::Serializer::DeserializeFloat(p_doc, p_node, "friction"));
	SetLinearFactor(Helpers::Serializer::DeserializeVec3(p_doc, p_node, "linear_factor"));
	SetAngularFactor(Helpers::Serializer::DeserializeVec3(p_doc, p_node, "angular_factor"));
	SetCollisionDetectionMode(static_cast<GePhysics::Entities::PhysicalObject::ECollisionDetectionMode>(Helpers::Serializer::DeserializeInt(p_doc, p_node, "collision_mode")));
}

void GeCore::ECS::Components::CPhysicalObject::OnInspector(GeUI::Internal::WidgetContainer & p_root)
{
	Helpers::GUIDrawer::DrawBoolean(p_root, "Trigger", std::bind(&CPhysicalObject::IsTrigger, this), std::bind(&CPhysicalObject::SetTrigger, this, std::placeholders::_1));
	Helpers::GUIDrawer::DrawBoolean(p_root, "Kinematic", std::bind(&CPhysicalObject::IsKinematic, this), std::bind(&CPhysicalObject::SetKinematic, this, std::placeholders::_1));
	Helpers::GUIDrawer::DrawScalar<float>(p_root, "Mass", std::bind(&CPhysicalObject::GetMass, this), std::bind(&CPhysicalObject::SetMass, this, std::placeholders::_1), 0.1f, 0.f, 10000.f);
	Helpers::GUIDrawer::DrawScalar<float>(p_root, "Bounciness", std::bind(&CPhysicalObject::GetBounciness, this), std::bind(&CPhysicalObject::SetBounciness, this, std::placeholders::_1), 0.1f, 0.f, 1.f);
	Helpers::GUIDrawer::DrawScalar<float>(p_root, "Friction", std::bind(&CPhysicalObject::GetFriction, this), std::bind(&CPhysicalObject::SetFriction, this, std::placeholders::_1), 0.1f, 0.f, 1.f);
	Helpers::GUIDrawer::DrawVec3(p_root, "Linear Factor", std::bind(&CPhysicalObject::GetLinearFactor, this), std::bind(&CPhysicalObject::SetLinearFactor, this, std::placeholders::_1), 0.1f, 0.f, 1.f);
	Helpers::GUIDrawer::DrawVec3(p_root, "Angular Factor", std::bind(&CPhysicalObject::GetAngularFactor, this), std::bind(&CPhysicalObject::SetAngularFactor, this, std::placeholders::_1), 0.1f, 0.f, 1.f);
	
	Helpers::GUIDrawer::CreateTitle(p_root, "Collision Mode");
	auto& collisionMode = p_root.CreateWidget<GeUI::Widgets::Selection::ComboBox>(static_cast<int>(GetCollisionDetectionMode()));
	collisionMode.choices.emplace(0, "Discrete");
	collisionMode.choices.emplace(1, "Continuous");
	collisionMode.ValueChangedEvent += [this](int p_choice)
	{
		SetCollisionDetectionMode(static_cast<GePhysics::Entities::PhysicalObject::ECollisionDetectionMode>(p_choice));
	};
}

void GeCore::ECS::Components::CPhysicalObject::Init()
{
	m_physicalObject->SetEnabled(false);
}

void GeCore::ECS::Components::CPhysicalObject::BindListener()
{
	m_physicalObject->CollisionStartEvent += [this](GePhysics::Entities::PhysicalObject& otherPhysicalObject)
	{
		auto& otherObject = otherPhysicalObject.GetUserData<std::reference_wrapper<CPhysicalObject>>().get();

		CollisionEnterEvent.Invoke(otherObject);
		owner.OnCollisionEnter(otherObject);
	};
	m_physicalObject->CollisionStayEvent += [this](GePhysics::Entities::PhysicalObject& otherPhysicalObject)
	{
		auto& otherObject = otherPhysicalObject.GetUserData<std::reference_wrapper<CPhysicalObject>>().get();

		CollisionStayEvent.Invoke(otherObject);
		owner.OnCollisionStay(otherObject);
	};
	m_physicalObject->CollisionStopEvent += [this](GePhysics::Entities::PhysicalObject& otherPhysicalObject)
	{
		auto& otherObject = otherPhysicalObject.GetUserData<std::reference_wrapper<CPhysicalObject>>().get();

		CollisionExitEvent.Invoke(otherObject);
		owner.OnCollisionExit(otherObject);
	};

	m_physicalObject->TriggerStartEvent += [this](GePhysics::Entities::PhysicalObject& otherPhysicalObject)
	{
		auto& otherObject = otherPhysicalObject.GetUserData<std::reference_wrapper<CPhysicalObject>>().get();

		TriggerEnterEvent.Invoke(otherObject);
		owner.OnTriggerEnter(otherObject);
	};
	m_physicalObject->TriggerStayEvent += [this](GePhysics::Entities::PhysicalObject& otherPhysicalObject)
	{
		auto& otherObject = otherPhysicalObject.GetUserData<std::reference_wrapper<CPhysicalObject>>().get();

		TriggerStayEvent.Invoke(otherObject);
		owner.OnTriggerStay(otherObject);
	};
	m_physicalObject->TriggerStopEvent += [this](GePhysics::Entities::PhysicalObject& otherPhysicalObject)
	{
		auto& otherObject = otherPhysicalObject.GetUserData<std::reference_wrapper<CPhysicalObject>>().get();

		TriggerExitEvent.Invoke(otherObject);
		owner.OnTriggerExit(otherObject);
	};
}

void GeCore::ECS::Components::CPhysicalObject::OnEnable()
{
	m_physicalObject->SetEnabled(true);
}

void GeCore::ECS::Components::CPhysicalObject::OnDisable()
{
	m_physicalObject->SetEnabled(false);
}
