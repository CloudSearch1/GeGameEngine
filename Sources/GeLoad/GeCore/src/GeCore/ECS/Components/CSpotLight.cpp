#include <GeUI/Widgets/Texts/Text.h>
#include <GeUI/Widgets/Drags/DragFloat.h>
#include <GeUI/Widgets/Selection/ColorEdit.h>
#include <GeUI/Widgets/Buttons/Button.h>
#include <GeUI/Widgets/Layout/Group.h>

#include "GeCore/ECS/Actor.h"

#include "GeCore/ECS/Components/CSpotLight.h"

GeCore::ECS::Components::CSpotLight::CSpotLight(ECS::Actor & p_owner) :
	CLight(p_owner)
{
	m_data.type = static_cast<float>(GeRendering::Entities::Light::Type::SPOT);
}

std::string GeCore::ECS::Components::CSpotLight::GetName()
{
	return "Spot Light";
}

float GeCore::ECS::Components::CSpotLight::GetConstant() const
{
	return m_data.constant;
}

float GeCore::ECS::Components::CSpotLight::GetLinear() const
{
	return m_data.linear;
}

float GeCore::ECS::Components::CSpotLight::GetQuadratic() const
{
	return m_data.quadratic;
}

float GeCore::ECS::Components::CSpotLight::GetCutoff() const
{
	return m_data.cutoff;
}

float GeCore::ECS::Components::CSpotLight::GetOuterCutoff() const
{
	return m_data.outerCutoff;
}

void GeCore::ECS::Components::CSpotLight::SetConstant(float p_constant)
{
	m_data.constant = p_constant;
}

void GeCore::ECS::Components::CSpotLight::SetLinear(float p_linear)
{
	m_data.linear = p_linear;
}

void GeCore::ECS::Components::CSpotLight::SetQuadratic(float p_quadratic)
{
	m_data.quadratic = p_quadratic;
}

void GeCore::ECS::Components::CSpotLight::SetCutoff(float p_cutoff)
{
	m_data.cutoff = p_cutoff;
}

void GeCore::ECS::Components::CSpotLight::SetOuterCutoff(float p_outerCutoff)
{
	m_data.outerCutoff = p_outerCutoff;
}

void GeCore::ECS::Components::CSpotLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace GeCore::Helpers;

	CLight::OnSerialize(p_doc, p_node);

	Serializer::SerializeFloat(p_doc, p_node, "constant", m_data.constant);
	Serializer::SerializeFloat(p_doc, p_node, "linear", m_data.linear);
	Serializer::SerializeFloat(p_doc, p_node, "quadratic", m_data.quadratic);
	Serializer::SerializeFloat(p_doc, p_node, "cutoff", m_data.cutoff);
	Serializer::SerializeFloat(p_doc, p_node, "outercutoff", m_data.outerCutoff);
}

void GeCore::ECS::Components::CSpotLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace GeCore::Helpers;

	CLight::OnDeserialize(p_doc, p_node);

	Serializer::DeserializeFloat(p_doc, p_node, "constant", m_data.constant);
	Serializer::DeserializeFloat(p_doc, p_node, "linear", m_data.linear);
	Serializer::DeserializeFloat(p_doc, p_node, "quadratic", m_data.quadratic);
	Serializer::DeserializeFloat(p_doc, p_node, "cutoff", m_data.cutoff);
	Serializer::DeserializeFloat(p_doc, p_node, "outercutoff", m_data.outerCutoff);
}

void GeCore::ECS::Components::CSpotLight::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{
	using namespace GeCore::Helpers;

	CLight::OnInspector(p_root);

	GUIDrawer::DrawScalar<float>(p_root, "Cut-Off", m_data.cutoff, 0.1f, 0.f, 180.f);
	GUIDrawer::DrawScalar<float>(p_root, "Outer Cut-Off", m_data.outerCutoff, 0.1f, 0.f, 180.f);

	GUIDrawer::CreateTitle(p_root, "Fall-off presets");
	auto& presetsRoot = p_root.CreateWidget<GeUI::Widgets::Layout::Group>();

	auto& constantPreset = presetsRoot.CreateWidget<GeUI::Widgets::Buttons::Button>("Constant");
	constantPreset.ClickedEvent += [this] { m_data.constant = 1.f, m_data.linear = m_data.quadratic = 0.f; };
	constantPreset.lineBreak = false;
	constantPreset.idleBackgroundColor = { 0.7f, 0.5f, 0.f };

	auto& linearPreset = presetsRoot.CreateWidget<GeUI::Widgets::Buttons::Button>("Linear");
	linearPreset.ClickedEvent += [this] { m_data.linear = 1.f, m_data.constant = m_data.quadratic = 0.f; };
	linearPreset.lineBreak = false;
	linearPreset.idleBackgroundColor = { 0.7f, 0.5f, 0.f };

	auto& quadraticPreset = presetsRoot.CreateWidget<GeUI::Widgets::Buttons::Button>("Quadratic");
	quadraticPreset.ClickedEvent += [this] { m_data.quadratic = 1.f, m_data.constant = m_data.linear = 0.f; };
	quadraticPreset.idleBackgroundColor = { 0.7f, 0.5f, 0.f };

	GUIDrawer::DrawScalar<float>(p_root, "Constant", m_data.constant, 0.005f, 0.f);
	GUIDrawer::DrawScalar<float>(p_root, "Linear", m_data.linear, 0.005f, 0.f);
	GUIDrawer::DrawScalar<float>(p_root, "Quadratic", m_data.quadratic, 0.005f, 0.f);
}
