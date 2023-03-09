#pragma once


#include "GeAudio/Core/AudioEngine.h"
#include "GeAudio/Resources/Sound.h"

namespace GeAudio::Core
{
	class AudioPlayer
	{
	public:
		AudioPlayer(AudioEngine& p_audioEngine);

		std::unique_ptr<Tracking::SoundTracker> PlaySound(const Resources::Sound& p_sound, bool p_autoPlay = true, bool p_looped = false, bool p_track = false);

		std::unique_ptr<Tracking::SoundTracker> PlaySpatialSound(const Resources::Sound& p_sound, bool p_autoPlay = true, bool p_looped = false, const GeMaths::FVector3& p_position = {0.0f, 0.0f, 0.0f}, bool p_track = false);

	private:
		AudioEngine& m_audioEngine;
	};
}
