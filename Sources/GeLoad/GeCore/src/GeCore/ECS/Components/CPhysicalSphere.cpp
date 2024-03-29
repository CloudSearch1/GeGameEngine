#include <GePhysics/Entities/PhysicalSphere.h>
#include <GeUI/Widgets/Drags/DragFloat.h>

#include "GeCore/ECS/Components/CPhysicalSphere.h"
#include "GeCore/ECS/Actor.h"

using namespace GePhysics::Entities;

GeCore::ECS::Components::CPhysicalSphere::CPhysicalSphere(ECS::Actor & p_owner) :
	CPhysicalObject(p_owner)
{
	m_physicalObject = std::make_unique<PhysicalSphere>(p_owner.transform.GetFTransform());

	m_physicalObject->SetUserData<std::reference_wrapper<CPhysicalObject>>(*this);

	BindListener();
	Init();
}

std::string GeCore::ECS::Components::CPhysicalSphere::GetName()
{
	return "Physical Sphere";
}

void GeCore::ECS::Components::CPhysicalSphere::SetRadius(float p_radius)
{
	GetPhysicalObjectAs<PhysicalSphere>().SetRadius(p_radius);
}

float GeCore::ECS::Components::CPhysicalSphere::GetRadius() const
{
	return GetPhysicalObjectAs<PhysicalSphere>().GetRadius();
}

void GeCore::ECS::Components::CPhysicalSphere::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CPhysicalObject::OnSerialize(p_doc, p_node);

	Helpers::Serializer::SerializeFloat(p_doc, p_node, "radius", GetRadius());
}

void GeCore::ECS::Components::CPhysicalSphere::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CPhysicalObject::OnDeserialize(p_doc, p_node);

	SetRadius(Helpers::Serializer::DeserializeFloat(p_doc, p_node, "radius"));
}

void GeCore::ECS::Components::CPhysicalSphere::OnInspector(GeUI::Internal::WidgetContainer & p_root)
{
	CPhysicalObject::OnInspector(p_root);

	Helpers::GUIDrawer::DrawScalar<float>(p_root, "Radius", std::bind(&CPhysicalSphere::GetRadius, this), std::bind(&CPhysicalSphere::SetRadius, this, std::placeholders::_1), 0.1f, 0.f, 100000.f);
}
