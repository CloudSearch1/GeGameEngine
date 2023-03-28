#pragma once

#include <irrklang/irrKlang.h>


#include "GeAudio/Tracking/SoundStopEventBinder.h"

namespace GeAudio::Tracking
{
	class SoundTracker
	{
	public:
		SoundTracker(irrklang::ISound* p_track);

		~SoundTracker();

		irrklang::ISound* GetTrack() const;

	public:
		GeUtils::Eventing::Event<> StopEvent;

	private:
		irrklang::ISound* const m_track = nullptr;

	private:
		SoundStopEventBinder m_soundStopEventBinder;
	};
}
