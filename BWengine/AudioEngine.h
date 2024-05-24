#pragma once

#include <string>
#include <map>

#include <SDL/SDL_mixer.h>

namespace BWengine {

	class SoundEffect {
	public:

		friend class AudioEngine;
		void play(int loops = 0, int volume = 128);

	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	class Music {
	public:

		friend class AudioEngine;
		// use -1 for forever
		void play(int loops = -1);

		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		bool init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:

		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;

		bool m_isInitialised = false;

	};
}


