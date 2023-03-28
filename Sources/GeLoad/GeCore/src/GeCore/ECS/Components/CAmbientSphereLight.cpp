#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Selection/ColorEdit.h>
#include <GeUI/Widgets/Buttons/Button.h>

#include "GeCore/ECS/Actor.h"

#include "GeCore/ECS/Components/CAmbientSphereLight.h"

GeCore::ECS::Components::CAmbientSphereLight::CAmbientSphereLight(ECS::Actor & p_owner) :
	CLight(p_owner)
{
    m_data.intensity = 0.1f;
	m_data.constant = 1.0f;

	m_data.type = static_cast<float>(GeRendering::Entities::Light::Type::AMBIENT_SPHERE);
}

std::string GeCore::ECS::Components::CAmbientSphereLight::GetName()
{
	return "Ambient Sphere Light";
}

float GeCore::ECS::Components::CAmbientSphereLight::GetRadius() const
{
	return m_data.quadratic;
}

void GeCore::ECS::Components::CAmbientSphereLight::SetRadius(float p_radius)
{
	m_data.constant = p_radius;
}

void GeCore::ECS::Components::CAmbientSphereLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace GeCore::Helpers;

	CLight::OnSerialize(p_doc, p_node);

	Serializer::SerializeFloat(p_doc, p_node, "radius", m_data.constant);
}

void GeCore::ECS::Components::CAmbientSphereLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace GeCore::Helpers;

	CLight::OnDeserialize(p_doc, p_node);

	Serializer::DeserializeFloat(p_doc, p_node, "radius", m_data.constant);
}

void GeCore::ECS::Components::CAmbientSphereLight::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{
	using namespace GeCore::Helpers;

	CLight::OnInspector(p_root);

	GUIDrawer::DrawScalar<float>(p_root, "Radius", m_data.constant, 0.1f, 0.f);
}
