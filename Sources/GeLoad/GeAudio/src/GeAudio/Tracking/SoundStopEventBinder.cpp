#include "GeAudio/Tracking/SoundStopEventBinder.h"

GeAudio::Tracking::SoundStopEventBinder::SoundStopEventBinder(GeUtils::Eventing::Event<>& p_soundFinishedEvent) : SoundFinishedEvent(p_soundFinishedEvent)
{
}

void GeAudio::Tracking::SoundStopEventBinder::OnSoundStopped(irrklang::ISound * sound, irrklang::E_STOP_EVENT_CAUSE reason, void * userData)
{
	SoundFinishedEvent.Invoke();
}
