#pragma once

#include <string>

namespace BWengine {

	enum class ErrorCodes {
		NO_ERROR = 0,
		SDL_ERROR = 1,
		SDL_WINDOW_ERROR = 2,
		SDL_CONTEXT_ERROR = 3,
		GLEW_INIT_ERROR = 4,
		READ_FILE_ERROR = 5,
		SHADER_CREATION_ERROR = 6,
		SHADER_COMPILATION_ERROR = 7,
		MISSING_SHADER_UNIFORM_ERROR = 8,
		SHADER_LINK_ERROR = 9,
		UNLOADED_SHEET_ERROR = 10,
		LOCALIZE_SOUND_CHANNEL_ERROR = 11,
		DOUBLE_AUDIO_ENGINE_ERROR = 12,
		MIX_INIT_ERROR = 13,
		MIX_OPEN_AUDIO_ERROR = 14,
		LOAD_WAV_FILE_ERROR = 15,
		LOAD_MUSIC_FILE_ERROR = 16,
	};
	
	extern void raiseLastError();
	extern void fatalError(std::string errorString);
	extern void setLastError(ErrorCodes code, std::string extraMesage = "");
	extern std::string getLastError();

}