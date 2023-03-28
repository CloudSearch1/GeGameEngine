#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Selection/ColorEdit.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Layout/Group.h>

#include "GeCore/ECS/Actor.h"

#include "GeCore/ECS/Components/CLight.h"

GeCore::ECS::Components::CLight::CLight(ECS::Actor & p_owner) :
	AComponent(p_owner),
	m_data(p_owner.transform.GetFTransform(), {})
{
}

const GeRendering::Entities::Light& GeCore::ECS::Components::CLight::GetData() const
{
	return m_data;
}

const GeMaths::FVector3& GeCore::ECS::Components::CLight::GetColor() const
{
	return m_data.color;
}

float GeCore::ECS::Components::CLight::GetIntensity() const
{
	return m_data.intensity;
}

void GeCore::ECS::Components::CLight::SetColor(const GeMaths::FVector3& p_color)
{
	m_data.color = p_color;
}

void GeCore::ECS::Components::CLight::SetIntensity(float p_intensity)
{
	m_data.intensity = p_intensity;
}

void GeCore::ECS::Components::CLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace GeCore::Helpers;

	Serializer::SerializeVec3(p_doc, p_node, "color", m_data.color);
	Serializer::SerializeFloat(p_doc, p_node, "intensity", m_data.intensity);
}

void GeCore::ECS::Components::CLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace GeCore::Helpers;

	Serializer::DeserializeVec3(p_doc, p_node, "color", m_data.color);
	Serializer::DeserializeFloat(p_doc, p_node, "intensity", m_data.intensity);
}

void GeCore::ECS::Components::CLight::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{
	using namespace GeCore::Helpers;

	GUIDrawer::DrawColor(p_root, "Color", reinterpret_cast<GeUI::Types::Color&>(m_data.color));
	GUIDrawer::DrawScalar<float>(p_root, "Intensity", m_data.intensity, 0.005f, GUIDrawer::_MIN_FLOAT, GUIDrawer::_MAX_FLOAT);
}
