#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Selection/ColorEdit.h>

#include "GeCore/ECS/Actor.h"

#include "GeCore/ECS/Components/CDirectionalLight.h"

GeCore::ECS::Components::CDirectionalLight::CDirectionalLight(ECS::Actor & p_owner) :
	CLight(p_owner)
{
	m_data.type = static_cast<float>(GeRendering::Entities::Light::Type::DIRECTIONAL);
}

std::string GeCore::ECS::Components::CDirectionalLight::GetName()
{
	return "Directional Light";
}

void GeCore::ECS::Components::CDirectionalLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CLight::OnSerialize(p_doc, p_node);
}

void GeCore::ECS::Components::CDirectionalLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CLight::OnDeserialize(p_doc, p_node);
}

void GeCore::ECS::Components::CDirectionalLight::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{
	CLight::OnInspector(p_root);
}
