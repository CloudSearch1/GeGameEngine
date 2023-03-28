#include <GePhysics/Entities/PhysicalBox.h>

#include "GeCore/ECS/Components/CPhysicalBox.h"
#include "GeCore/ECS/Actor.h"

using namespace GePhysics::Entities;

GeCore::ECS::Components::CPhysicalBox::CPhysicalBox(ECS::Actor & p_owner) :
	CPhysicalObject(p_owner)
{
	m_physicalObject = std::make_unique<GePhysics::Entities::PhysicalBox>(p_owner.transform.GetFTransform());

	m_physicalObject->SetUserData<std::reference_wrapper<CPhysicalObject>>(*this);

	BindListener();
	Init();
}

std::string GeCore::ECS::Components::CPhysicalBox::GetName()
{
	return "Physical Box";
}

void GeCore::ECS::Components::CPhysicalBox::SetSize(const GeMaths::FVector3 & p_size)
{
	GetPhysicalObjectAs<PhysicalBox>().SetSize(p_size);
}

GeMaths::FVector3 GeCore::ECS::Components::CPhysicalBox::GetSize() const
{
	return GetPhysicalObjectAs<PhysicalBox>().GetSize();
}

void GeCore::ECS::Components::CPhysicalBox::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CPhysicalObject::OnSerialize(p_doc, p_node);

	Helpers::Serializer::SerializeVec3(p_doc, p_node, "size", GetSize());
}

void GeCore::ECS::Components::CPhysicalBox::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CPhysicalObject::OnDeserialize(p_doc, p_node);

	SetSize(Helpers::Serializer::DeserializeVec3(p_doc, p_node, "size"));
}

void GeCore::ECS::Components::CPhysicalBox::OnInspector(GeUI::Internal::WidgetContainer & p_root)
{
	CPhysicalObject::OnInspector(p_root);

	Helpers::GUIDrawer::DrawVec3(p_root, "Size", std::bind(&CPhysicalBox::GetSize, this), std::bind(&CPhysicalBox::SetSize, this, std::placeholders::_1), 0.1f, 0.f, 100000.f);
}
