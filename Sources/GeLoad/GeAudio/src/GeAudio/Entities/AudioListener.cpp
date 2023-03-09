#include "GeAudio/Entities/AudioListener.h"

GeUtils::Eventing::Event<GeAudio::Entities::AudioListener&>	GeAudio::Entities::AudioListener::CreatedEvent;
GeUtils::Eventing::Event<GeAudio::Entities::AudioListener&>	GeAudio::Entities::AudioListener::DestroyedEvent;

GeAudio::Entities::AudioListener::AudioListener() :
	m_transform(new GeMaths::FTransform()),
	m_internalTransform(true)
{
	Setup();
}

GeAudio::Entities::AudioListener::AudioListener(GeMaths::FTransform& p_transform) :
	m_transform(&p_transform),
	m_internalTransform(false)
{
	Setup();
}

GeAudio::Entities::AudioListener::~AudioListener()
{
	DestroyedEvent.Invoke(*this);
}

GeMaths::FTransform& GeAudio::Entities::AudioListener::GetTransform()
{
	return *m_transform;
}

void GeAudio::Entities::AudioListener::SetEnabled(bool p_enable)
{
	m_enabled = p_enable;
}

bool GeAudio::Entities::AudioListener::IsEnabled() const
{
	return m_enabled;
}

void GeAudio::Entities::AudioListener::Setup()
{
	CreatedEvent.Invoke(*this);
}
