#pragma once

#include <memory>

#include "BWengine.h"
#include "Window.h"
#include "InputManager.h"

namespace BWengine {

	class ScreenList;

	class IGameScreen;

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run(const float desiredFps);
		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);

		const float getFps() { return m_fps; }



	protected:

		virtual void update();
		virtual void draw();


		bool init();
		bool initSystems();

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;
		bool m_isRunning = false;
		float m_fps = 0;
		Window m_window;

		InputManager m_inputManager;
	};
}


