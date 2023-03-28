#pragma once

#include <GeAudio/Entities/AudioSource.h>
#include <GeUtils/Eventing/Event.h>

#include "GeCore/ECS/Components/AComponent.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
	class CAudioSource : public AComponent
	{
	public:
		CAudioSource(ECS::Actor& p_owner);

		std::string GetName() override;

		void SetSound(GeAudio::Resources::Sound* p_sound);

		void SetAutoplay(bool p_autoplay);

		void SetVolume(float p_volume);

		void SetPan(float p_pan);

    void SetLooped(bool p_looped);

		void SetPitch(float p_pitch);

		void SetSpatial(bool p_value);

		void SetAttenuationThreshold(float p_distance);

		GeAudio::Resources::Sound* GetSound() const;

    bool IsAutoplayed() const;

		float GetVolume() const;

		float GetPan() const;

		bool IsLooped() const;

		float GetPitch() const;

		bool IsFinished() const;

		bool IsSpatial() const;

		float GetAttenuationThreshold() const;

		void Play();

		void Resume();

		void Pause();

		void Stop();

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	private:
		virtual void OnEnable() override;
		virtual void OnDisable() override;

	private:
		GeAudio::Resources::Sound* m_sound = nullptr;
		GeAudio::Entities::AudioSource m_audioSource;
		bool m_autoPlay = false;
	};
}
