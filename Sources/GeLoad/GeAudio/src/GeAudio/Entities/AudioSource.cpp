#include <irrklang/ik_vec3d.h>

#include "GeAudio/Core/AudioPlayer.h"
#include "GeAudio/Entities/AudioSource.h"

GeUtils::Eventing::Event<GeAudio::Entities::AudioSource&> GeAudio::Entities::AudioSource::CreatedEvent;
GeUtils::Eventing::Event<GeAudio::Entities::AudioSource&> GeAudio::Entities::AudioSource::DestroyedEvent;

GeAudio::Entities::AudioSource::AudioSource(Core::AudioPlayer& p_audioPlayer) :
	m_audioPlayer(p_audioPlayer),
	m_transform(new GeMaths::FTransform()),
	m_internalTransform(true)
{
	Setup();
}

GeAudio::Entities::AudioSource::AudioSource(Core::AudioPlayer& p_audioPlayer, GeMaths::FTransform& p_transform) :
	m_audioPlayer(p_audioPlayer),
	m_transform(&p_transform),
	m_internalTransform(false)
{
	Setup();
}

void GeAudio::Entities::AudioSource::Setup()
{
	CreatedEvent.Invoke(*this);
}

GeAudio::Entities::AudioSource::~AudioSource()
{
	DestroyedEvent.Invoke(*this);

	StopAndDestroyTrackedSound();

	if (m_internalTransform)
		delete m_transform;
}

void GeAudio::Entities::AudioSource::UpdateTrackedSoundPosition()
{
	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setPosition(reinterpret_cast<const irrklang::vec3df&>(m_transform->GetWorldPosition())); // FVector3 and vec3df have the same data layout
}

void GeAudio::Entities::AudioSource::ApplySourceSettingsToTrackedSound()
{
	m_trackedSound->GetTrack()->setVolume(m_volume);
	m_trackedSound->GetTrack()->setPan(m_pan);
	m_trackedSound->GetTrack()->setIsLooped(m_looped);
	m_trackedSound->GetTrack()->setPlaybackSpeed(m_pitch);
	m_trackedSound->GetTrack()->setMinDistance(m_attenuationThreshold);
}

void GeAudio::Entities::AudioSource::SetSpatial(bool p_value)
{
	m_spatial = p_value;
}

void GeAudio::Entities::AudioSource::SetAttenuationThreshold(float p_distance)
{
	m_attenuationThreshold = p_distance;

	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setMinDistance(p_distance);
}

GeAudio::Tracking::SoundTracker* GeAudio::Entities::AudioSource::GetTrackedSound() const
{
	return m_trackedSound.get();
}

void GeAudio::Entities::AudioSource::SetVolume(float p_volume)
{
	m_volume = p_volume;

	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setVolume(p_volume);
}

void GeAudio::Entities::AudioSource::SetPan(float p_pan)
{
	m_pan = p_pan;

	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setPan(p_pan * -1.0f);
}

void GeAudio::Entities::AudioSource::SetLooped(bool p_looped)
{
	m_looped = p_looped;

	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setIsLooped(p_looped);
}

void GeAudio::Entities::AudioSource::SetPitch(float p_pitch)
{
	m_pitch = p_pitch;

	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setPlaybackSpeed(p_pitch < 0.01f ? 0.01f : p_pitch);
}

bool GeAudio::Entities::AudioSource::IsTrackingSound() const
{
	return m_trackedSound.operator bool();
}

bool GeAudio::Entities::AudioSource::IsSpatial() const
{
	return m_spatial;
}

float GeAudio::Entities::AudioSource::GetAttenuationThreshold() const
{
	return m_attenuationThreshold;
}

float GeAudio::Entities::AudioSource::GetVolume() const
{
	return m_volume;
}

float GeAudio::Entities::AudioSource::GetPan() const
{
	return m_pan;
}

bool GeAudio::Entities::AudioSource::IsLooped() const
{
	return m_looped;
}

float GeAudio::Entities::AudioSource::GetPitch() const
{
	return m_pitch;
}

bool GeAudio::Entities::AudioSource::IsFinished() const
{
	if (IsTrackingSound())
		return m_trackedSound->GetTrack()->isFinished();
	else
		return true;
}

void GeAudio::Entities::AudioSource::Play(const Resources::Sound& p_sound)
{
	StopAndDestroyTrackedSound();
	
	if (m_spatial)
		m_trackedSound = m_audioPlayer.PlaySpatialSound(p_sound, false, m_looped, m_transform->GetWorldPosition(), true);
	else
		m_trackedSound = m_audioPlayer.PlaySound(p_sound, false, m_looped, true);

	if (IsTrackingSound())
	{
		m_trackedSound->GetTrack()->setVolume(m_volume);
		m_trackedSound->GetTrack()->setPan(m_pan);
		m_trackedSound->GetTrack()->setPlaybackSpeed(m_pitch);
		m_trackedSound->GetTrack()->setMinDistance(m_attenuationThreshold);
		m_trackedSound->GetTrack()->setIsPaused(false);
	}
}

void GeAudio::Entities::AudioSource::Resume()
{
	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setIsPaused(false);
}

void GeAudio::Entities::AudioSource::Pause()
{
	if (IsTrackingSound())
		m_trackedSound->GetTrack()->setIsPaused(true);
}

void GeAudio::Entities::AudioSource::Stop()
{
	if (IsTrackingSound())
		m_trackedSound->GetTrack()->stop();
}

void GeAudio::Entities::AudioSource::StopAndDestroyTrackedSound()
{
	if (IsTrackingSound())
	{
		m_trackedSound->GetTrack()->stop();
		m_trackedSound->GetTrack()->drop();
	}
}
