#include "GeAudio/Tracking/SoundTracker.h"

GeAudio::Tracking::SoundTracker::SoundTracker(irrklang::ISound* p_track) :
	m_track(p_track),
	m_soundStopEventBinder(StopEvent)
{
}

GeAudio::Tracking::SoundTracker::~SoundTracker()
{
}

irrklang::ISound* GeAudio::Tracking::SoundTracker::GetTrack() const
{
	return m_track;
}
