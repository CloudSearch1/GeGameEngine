#include "GeCore/ECS/Components/CAudioListener.h"
#include "GeCore/ECS/Actor.h"

GeCore::ECS::Components::CAudioListener::CAudioListener(ECS::Actor& p_owner) :
	AComponent(p_owner),
	m_audioListener(owner.transform.GetFTransform())
{
	m_audioListener.SetEnabled(false);
}

std::string GeCore::ECS::Components::CAudioListener::GetName()
{
	return "Audio Listener";
}

void GeCore::ECS::Components::CAudioListener::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

void GeCore::ECS::Components::CAudioListener::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

void GeCore::ECS::Components::CAudioListener::OnInspector(GeUI::Internal::WidgetContainer& p_root)
{

}

void GeCore::ECS::Components::CAudioListener::OnEnable()
{
	m_audioListener.SetEnabled(true);
}

void GeCore::ECS::Components::CAudioListener::OnDisable()
{
	m_audioListener.SetEnabled(false);
}
