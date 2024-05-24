#include "AudioEngine.h"

#include "BWengineErrors.h"


namespace BWengine {

	void SoundEffect::play(int loops /* = 0*/, int volume /* = 128*/)
	{
		//dont play empty sound effects
		if (m_chunk == nullptr) {
			return;
		}
		int channel = Mix_PlayChannel(-1, m_chunk, loops);

		//when failed to find channel pick channel 0
		if (channel == -1) {
			channel = Mix_PlayChannel(0, m_chunk, loops);
			if (channel == -1) {
				setLastError(ErrorCodes::LOCALIZE_SOUND_CHANNEL_ERROR, std::string(Mix_GetError()));
				raiseLastError();
			}
		}
		Mix_Volume(channel, volume);
	}

	void Music::play(int loops /* = -1*/)
	{ 
		Mix_PlayMusic(m_music, loops);
	} 

	void Music::pause() 
	{
		Mix_PausedMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}


	AudioEngine::AudioEngine() {
	}

	AudioEngine::~AudioEngine() {
		destroy();
	}

	bool AudioEngine::init()
	{
		if (m_isInitialised) {
			setLastError(ErrorCodes::DOUBLE_AUDIO_ENGINE_ERROR);
			return false;
		}
		if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == -1) {
			setLastError(ErrorCodes::MIX_INIT_ERROR, std::string(Mix_GetError()));
			return false;
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			setLastError(ErrorCodes::MIX_OPEN_AUDIO_ERROR, std::string(Mix_GetError()));
			return false;
		}

		m_isInitialised = true;
		return true;
	}

	void AudioEngine::destroy()
	{
		if (m_isInitialised) {
			m_isInitialised = false;

			for (auto& it : m_effectMap) {
				Mix_FreeChunk(it.second);
			}

			for (auto& it : m_musicMap) {
				Mix_FreeMusic(it.second);
			}

			m_effectMap.clear();
			m_musicMap.clear();

			Mix_CloseAudio();

			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath)
	{
		auto it = m_effectMap.find(filePath);

		SoundEffect effect;

		if (it == m_effectMap.end()) {
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr) {
				setLastError(ErrorCodes::LOAD_WAV_FILE_ERROR, std::string(Mix_GetError()));
				raiseLastError();
			}

			effect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else {
			effect.m_chunk = it->second;
		}

		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath)
	{
		auto it = m_musicMap.find(filePath);

		Music music;

		if (it == m_musicMap.end()) {
			Mix_Music* mixMuic = Mix_LoadMUS(filePath.c_str());
			if (mixMuic == nullptr) {
				setLastError(ErrorCodes::LOAD_MUSIC_FILE_ERROR, std::string(Mix_GetError()));
				raiseLastError();
			}

			music.m_music = mixMuic;
			m_musicMap[filePath] = mixMuic;
		}
		else {
			music.m_music = it->second;
		}

		return music;
	}
}
