#pragma once

#include <vector>
#include <optional>


#include "GeAudio/Entities/AudioSource.h"
#include "GeAudio/Entities/AudioListener.h"

namespace GeAudio::Core
{
	class AudioEngine
	{
	public:
		AudioEngine(const std::string& p_workingDirectory);

		~AudioEngine();

		void Update();

		void Suspend();

		void Unsuspend();

		bool IsSuspended() const;

		const std::string& GetWorkingDirectory() const;

		irrklang::ISoundEngine* GetIrrklangEngine() const;

		std::optional<std::pair<GeMaths::FVector3, GeMaths::FVector3>> GetListenerInformation(bool p_considerDisabled = false) const;

	private:
		void Consider(Entities::AudioSource& p_audioSource);
		void Consider(Entities::AudioListener& p_audioListener);

		void Unconsider(Entities::AudioSource& p_audioSource);
		void Unconsider(Entities::AudioListener& p_audioListener);

	private:
		const std::string m_workingDirectory;
		bool m_suspended = false;

		std::vector<std::reference_wrapper<Entities::AudioSource>> m_audioSources;
		std::vector<std::reference_wrapper<Entities::AudioSource>> m_suspendedAudioSources;
		std::vector<std::reference_wrapper<Entities::AudioListener>> m_audioListeners;
		
		irrklang::ISoundEngine* m_irrklangEngine = nullptr;
	};
}
