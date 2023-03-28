#pragma once

#include "AComponent.h"

#include <GeUtils/Eventing/Event.h>

#include <GeAudio/Entities/AudioListener.h>

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //代表一个音频监听器。 音频源和音频收听者之间的距离会影响声音
	class CAudioListener : public AComponent
	{
	public:
		CAudioListener(ECS::Actor& p_owner);

		std::string GetName() override;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	private:
		virtual void OnEnable() override;
		virtual void OnDisable() override;

	private:
		GeAudio::Entities::AudioListener m_audioListener;
	};
}
