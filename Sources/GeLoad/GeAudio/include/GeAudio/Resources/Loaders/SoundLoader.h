#pragma once

#include <string>

#include "GeAudio/Resources/Sound.h"

namespace GeAudio::Resources::Loaders
{
	class SoundLoader
	{
	public:
		SoundLoader() = delete;

		static Sound* Create(const std::string& p_filepath);

		static void Reload(Sound& p_sound, const std::string& p_path);

		static bool Destroy(Sound*& p_soundInstance);
	};
}
