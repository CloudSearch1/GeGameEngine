#pragma once


#include "GeMaths/FVector3.h"
#include "GeMaths/FTransform.h"

#include "GeAudio/Entities/AudioSource.h"

namespace GeAudio::Entities
{
	class AudioListener
	{
	public:
		AudioListener();

		AudioListener(GeMaths::FTransform& p_transform);

		~AudioListener();

		GeMaths::FTransform& GetTransform();

		void SetEnabled(bool p_enable);

		bool IsEnabled() const;

	private:
		void Setup();

	private:
		GeMaths::FTransform* const		m_transform;
		const bool						m_internalTransform;
		bool							m_enabled = true;

	public:
		static GeUtils::Eventing::Event<AudioListener&>	CreatedEvent;
		static GeUtils::Eventing::Event<AudioListener&>	DestroyedEvent;
	};
}
