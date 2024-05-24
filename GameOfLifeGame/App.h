#pragma once

#include <BWengine/IMainGame.h>
#include <BWengine/AudioEngine.h>

#include "GamePLayScreen.h"

class App : public BWengine::IMainGame
{
public:
	App();
	~App();


	void onInit() override;
	void addScreens()override;
	void onExit() override;

private:
	std::unique_ptr<GamePlayScreen> m_gamePlayScreen = nullptr;
	BWengine::AudioEngine m_audioEngine;

};

