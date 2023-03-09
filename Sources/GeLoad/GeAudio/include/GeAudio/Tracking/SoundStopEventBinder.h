#pragma once

#include <irrklang/irrKlang.h>
#include <irrklang/ik_ISoundStopEventReceiver.h>

#include <GeUtils/Eventing/Event.h>

namespace GeAudio::Tracking
{
	class SoundStopEventBinder : public irrklang::ISoundStopEventReceiver
	{
	public:
		SoundStopEventBinder(GeUtils::Eventing::Event<>& p_soundFinishedEvent);

		virtual void OnSoundStopped(irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData) override;

	private:
		GeUtils::Eventing::Event<>& SoundFinishedEvent;
	};
}
