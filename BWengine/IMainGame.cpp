#include "IMainGame.h"

#include <SDL/SDL.h>

#include "Timing.h"
#include "Vertex.h"
#include "ScreenList.h"
#include "IGameScreen.h"
#include "BWengineErrors.h"

namespace BWengine {
	IMainGame::IMainGame()
	{
		m_screenList = std::make_unique<ScreenList>(this);
	}

	IMainGame::~IMainGame()
	{
	}

	void IMainGame::run(const float desiredFps)
	{
		if (!init()) {
			fatalError(getLastError());
		}

		FpsLimiter limiter;
		limiter.setMaxFPS(desiredFps);

		m_isRunning = true;
		while (m_isRunning) {
			limiter.beginFrame();

			m_inputManager.update();
			update();
			if (m_isRunning) {
				draw();

				m_fps = limiter.endFrame();
				m_window.swapBuffer();
			}
			
		}
	}

	void IMainGame::exitGame()
	{
		m_currentScreen->onExit();
		// allow for proper disposal of resources
		m_currentScreen->setScreenState(ScreenState::EXIT_APPLICATION);
		if (m_screenList) {
			m_screenList->destroy();
			m_screenList.reset();
		}
		m_isRunning = false;

		onExit();
	}

	void IMainGame::onSDLEvent(SDL_Event& evnt) {
		switch (evnt.type)
		{
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			m_inputManager.setScrolled((float)evnt.wheel.x, (float)evnt.wheel.y);
		}
	}

	bool IMainGame::init()
	{
		if (BWengine::init() != 0) {
			return false;
		}

		if (!initSystems()) {
			return false;
		}

		onInit();
		addScreens();

		m_currentScreen = m_screenList->getCurrent();
		m_currentScreen->onEntry();
		m_currentScreen->setRunning();

		return true;
	}

	bool IMainGame::initSystems()
	{
		if (m_window.init("", 1600, 800, 0) != 0) {
			return false;
		}
		return true;
	}

	void IMainGame::update() {
		if (m_currentScreen) {
			switch (m_currentScreen->getState()) {
			case ScreenState::RUNNING:
				m_currentScreen->update();
				m_currentScreen->setFps(m_fps);
				break;

			case ScreenState::CHANGE_NEXT:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveNext();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::CHANGE_PREVIOUS:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->movePrevious();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;
			default:
				break;
			}
		}
		else {
			exitGame();
		}
	}

	void IMainGame::draw() {

		glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
			m_currentScreen->draw();
		}
	}
}

