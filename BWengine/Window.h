#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include "Vertex.h"


namespace BWengine {

	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int init(std::string windowName, int screenWidth, int screenHeight,
			unsigned int currentFlags);

		void swapBuffer();

		//getters
		int getScreenWidth() { return m_screenWidth; }
		int getScreenHeight() { return m_screenHeight; }

		//setters
		void setColor(ColorRGBA8 newColor);

	private:
		SDL_Window* m_sdlWindow;
		int m_screenWidth, m_screenHeight;

		int create(std::string windowName, unsigned int currentFlags);

	};

}