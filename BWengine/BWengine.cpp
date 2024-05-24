#include "BWengine.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "BWengineErrors.h"

namespace BWengine {


	int init()
	{
		// innit SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			setLastError(ErrorCodes::SDL_ERROR);
			return 1;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // prevent flickering

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		return 0;
	}

}