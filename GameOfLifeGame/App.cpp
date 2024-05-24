#include "App.h"

#include <BWengine/ScreenList.h>

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
	m_audioEngine.init();
}

void App::addScreens()
{
	m_gamePlayScreen = std::make_unique<GamePlayScreen>(&m_window, &m_inputManager, &m_audioEngine);

	m_screenList->addScreen(m_gamePlayScreen.get());
	m_screenList->setScreen(m_gamePlayScreen->getIndex());
}

void App::onExit()
{
}
