#include "BWengineErrors.h"

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

namespace BWengine {

	ErrorCodes LAST_ERROR = ErrorCodes::NO_ERROR;
	std::string EXTRA_MESSAGE = "";

	void raiseLastError() {
		fatalError(getLastError());
	}

	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		SDL_Quit();
		exit(420); // to dank 4 u
	}

	std::string getLastError() {
		std::string baseMessage;

		switch (LAST_ERROR) {
		case ErrorCodes::NO_ERROR:
			baseMessage =  "";
			break;
		case ErrorCodes::SDL_ERROR:
			baseMessage = SDL_GetError();
			break;
		case ErrorCodes::SDL_WINDOW_ERROR:
			baseMessage = "SDL window failed to create! ";
			break;
		case ErrorCodes::SDL_CONTEXT_ERROR:
			baseMessage = "SDL_GL context failed to create! ";
			break;
		case ErrorCodes::GLEW_INIT_ERROR:
			baseMessage = "GLEW failed to innitialise! ";
			break;
		case ErrorCodes::READ_FILE_ERROR:
			baseMessage = "Failed to read file: ";
			break;
		case ErrorCodes::SHADER_CREATION_ERROR:
			baseMessage = "Failed to create shader of type: ";
			break;
		case ErrorCodes::SHADER_COMPILATION_ERROR:
			baseMessage = "Failed to compile shader! ";
			break;
		case ErrorCodes::MISSING_SHADER_UNIFORM_ERROR:
			baseMessage = "Following uniform is not defined in shader: ";
			break;
		case ErrorCodes::SHADER_LINK_ERROR:
			baseMessage = "Shader failed to link. Log message: ";
			break;
		case ErrorCodes::UNLOADED_SHEET_ERROR:
			baseMessage = "The following sheet is not loaded and cannot be retrieved: ";
			break;
		case ErrorCodes::LOCALIZE_SOUND_CHANNEL_ERROR:
			baseMessage = "No audio channel is obtainable. SDL_Mix returned the following error: ";
			break;
		case ErrorCodes::DOUBLE_AUDIO_ENGINE_ERROR:
			baseMessage = "Can not innitialize audio engine twice!";
			break;
		case ErrorCodes::MIX_INIT_ERROR:
			baseMessage = "Mix init error: ";
			break;
		case ErrorCodes::MIX_OPEN_AUDIO_ERROR:
			baseMessage = "Mix open audio error: ";
			break;
		case ErrorCodes::LOAD_WAV_FILE_ERROR:
			baseMessage = "Mix_loadWAV error: ";
			break;
		case ErrorCodes::LOAD_MUSIC_FILE_ERROR:
			baseMessage = "Mix_LoadMUS error: ";
			break;
		default:
			baseMessage = "";
			break;
		}
		return "BWengine Error: " + baseMessage + EXTRA_MESSAGE;
	}

	void setLastError(ErrorCodes code, std::string extraMesage/*= ""*/) {
		LAST_ERROR = code;
		EXTRA_MESSAGE = extraMesage;
	}

}