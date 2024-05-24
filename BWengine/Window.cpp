#include "Window.h"
#include "BWengineErrors.h"
#include "Vertex.h"

namespace BWengine {

	Window::Window()
	{

	}

	Window::~Window()
	{

	}

	int Window::init(std::string windowName, int screenWidth, int screenHeight,
		unsigned int currentFlags)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		return create(windowName, currentFlags);
	}

	int Window::create(std::string windowName, unsigned int currentFlags)
	{

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		m_sdlWindow = SDL_CreateWindow(windowName.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
		if (m_sdlWindow == nullptr) {
			setLastError(ErrorCodes::SDL_WINDOW_ERROR);
			return 1;
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
		if (glContext == nullptr) {
			setLastError(ErrorCodes::SDL_CONTEXT_ERROR);
			return 2;
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			setLastError(ErrorCodes::GLEW_INIT_ERROR);
			return 3;
		}

		std::printf("***    OpenGL Version: %s    ***\n", glGetString(GL_VERSION));


		//set VSync
		SDL_GL_SetSwapInterval(0);

		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		return 0;
	}

	void Window::setColor(ColorRGBA8 newColor)
	{
		glClearColor(newColor.r / 255.0f, newColor.g / 255.0f, newColor.b / 255.0f,
			newColor.a / 255.0f);
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(m_sdlWindow); // swap double buffer
	}
}