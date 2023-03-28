#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Drags/DragMultipleFloats.h>

#include "GeCore/ECS/Components/CTransform.h"

GeCore::ECS::Components::CTransform::CTransform(ECS::Actor& p_owner, GeMaths::FVector3 p_localPosition, GeMaths::FQuaternion p_localRotation, GeMaths::FVector3 p_localScale) :
AComponent(p_owner)
{
	m_transform.GenerateMatrices(p_localPosition, p_localRotation, p_localScale);
}

std::string GeCore::ECS::Components::CTransform::GetName()
{
	return "Transform";
}

void GeCore::ECS::Components::CTransform::SetParent(CTransform& p_parent)
{
	m_transform.SetParent(p_parent.GetFTransform());
}

bool GeCore::ECS::Components::CTransform::RemoveParent()
{
	return m_transform.RemoveParent();
}

bool GeCore::ECS::Components::CTransform::HasParent() const
{
	return m_transform.HasParent();
}

void GeCore::ECS::Components::CTransform::SetLocalPosition(GeMaths::FVector3 p_newPosition)
{
	m_transform.SetLocalPosition(p_newPosition);
}

void GeCore::ECS::Components::CTransform::SetLocalRotation(GeMaths::FQuaternion p_newRotation)
{
	m_transform.SetLocalRotation(p_newRotation);
}

void GeCore::ECS::Components::CTransform::SetLocalScale(GeMaths::FVector3 p_newScale)
{
	m_transform.SetLocalScale(p_newScale);
}

void GeCore::ECS::Components::CTransform::SetWorldPosition(GeMaths::FVector3 p_newPosition)
{
	m_transform.SetWorldPosition(p_newPosition);
}

void GeCore::ECS::Components::CTransform::SetWorldRotation(GeMaths::FQuaternion p_newRotation)
{
	m_transform.SetWorldRotation(p_newRotation);
}

void GeCore::ECS::Components::CTransform::SetWorldScale(GeMaths::FVector3 p_newScale)
{
	m_transform.SetWorldScale(p_newScale);
}

void GeCore::ECS::Components::CTransform::TranslateLocal(const GeMaths::FVector3 & p_translation)
{
	m_transform.TranslateLocal(p_translation);
}

void GeCore::ECS::Components::CTransform::RotateLocal(const GeMaths::FQuaternion & p_rotation)
{
	m_transform.RotateLocal(p_rotation);
}

void GeCore::ECS::Components::CTransform::ScaleLocal(const GeMaths::FVector3 & p_scale)
{
	m_transform.ScaleLocal(p_scale);
}

const GeMaths::FVector3 & GeCore::ECS::Components::CTransform::GetLocalPosition() const
{
	return m_transform.GetLocalPosition();
}

const GeMaths::FQuaternion & GeCore::ECS::Components::CTransform::GetLocalRotation() const
{
	return m_transform.GetLocalRotation();
}

const GeMaths::FVector3 & GeCore::ECS::Components::CTransform::GetLocalScale() const
{
	return m_transform.GetLocalScale();
}

const GeMaths::FVector3 & GeCore::ECS::Components::CTransform::GetWorldPosition() const
{
	return m_transform.GetWorldPosition();
}

const GeMaths::FQuaternion & GeCore::ECS::Components::CTransform::GetWorldRotation() const
{
	return m_transform.GetWorldRotation();
}

const GeMaths::FVector3 & GeCore::ECS::Components::CTransform::GetWorldScale() const
{
	return m_transform.GetWorldScale();
}

const GeMaths::FMatrix4 & GeCore::ECS::Components::CTransform::GetLocalMatrix() const
{
	return m_transform.GetLocalMatrix();
}

const GeMaths::FMatrix4 & GeCore::ECS::Components::CTransform::GetWorldMatrix() const
{
	return m_transform.GetWorldMatrix();
}

GeMaths::FTransform & GeCore::ECS::Components::CTransform::GetFTransform()
{
	return m_transform;
}

GeMaths::FVector3 GeCore::ECS::Components::CTransform::GetWorldForward() const
{
	return m_transform.GetWorldForward();
}

GeMaths::FVector3 GeCore::ECS::Components::CTransform::GetWorldUp() const
{
	return m_transform.GetWorldUp();
}

GeMaths::FVector3 GeCore::ECS::Components::CTransform::GetWorldRight() const
{
	return m_transform.GetWorldRight();
}

GeMaths::FVector3 GeCore::ECS::Components::CTransform::GetLocalForward() const
{
	return m_transform.GetLocalForward();
}

GeMaths::FVector3 GeCore::ECS::Components::CTransform::GetLocalUp() const
{
	return m_transform.GetLocalUp();
}

GeMaths::FVector3 GeCore::ECS::Components::CTransform::GetLocalRight() const
{
	return m_transform.GetLocalRight();
}

void GeCore::ECS::Components::CTransform::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	GeCore::Helpers::Serializer::SerializeVec3(p_doc, p_node, "position", GetLocalPosition());
	GeCore::Helpers::Serializer::SerializeQuat(p_doc, p_node, "rotation", GetLocalRotation());
	GeCore::Helpers::Serializer::SerializeVec3(p_doc, p_node, "scale", GetLocalScale());
}

void GeCore::ECS::Components::CTransform::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	m_transform.GenerateMatrices
	(
		GeCore::Helpers::Serializer::DeserializeVec3(p_doc, p_node, "position"),
		GeCore::Helpers::Serializer::DeserializeQuat(p_doc, p_node, "rotation"),
		GeCore::Helpers::Serializer::DeserializeVec3(p_doc, p_node, "scale")
	);
}

void GeCore::ECS::Components::CTransform::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{
	auto getRotation = [this]
	{ 
		return GeMaths::FQuaternion::EulerAngles(GetLocalRotation());
	};

	auto setRotation = [this](GeMaths::FVector3 result)
	{
		SetLocalRotation(GeMaths::FQuaternion(result));
	};

	GeCore::Helpers::GUIDrawer::DrawVec3(p_root, "Position", std::bind(&CTransform::GetLocalPosition, this), std::bind(&CTransform::SetLocalPosition, this, std::placeholders::_1), 0.05f);
	GeCore::Helpers::GUIDrawer::DrawVec3(p_root, "Rotation", getRotation, setRotation, 0.05f);
	GeCore::Helpers::GUIDrawer::DrawVec3(p_root, "Scale", std::bind(&CTransform::GetLocalScale, this), std::bind(&CTransform::SetLocalScale, this, std::placeholders::_1), 0.05f, 0.0001f);
}
