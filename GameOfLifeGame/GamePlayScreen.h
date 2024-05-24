#pragma once

#include <memory>
#include <vector>

#include <BWengine/IGameScreen.h>
#include <BWengine/SpriteBatch.h>
#include <BWengine/GLSLProgram.h>
#include <BWengine/Camera2D.h>
#include <BWengine/Window.h>
#include <BWengine/GLTexture.h>
#include <BWengine/SpriteFont.h>
#include <BWengine/AudioEngine.h>
#include <BWengine/InputManager.h>

#include "Block.h"
#include "World.h"


class GamePlayScreen : public BWengine::IGameScreen
{
public:
	GamePlayScreen(BWengine::Window* window, BWengine::InputManager* inputManager, BWengine::AudioEngine* audioEngine);
	~GamePlayScreen();

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
	virtual void draw() override;
	

private:
	void updateCameraPosition();

	void checkInput();
	void drawHud();

	BWengine::SpriteBatch m_hudSpriteBatch;
	BWengine::GLSLProgram m_textureProgram;
	BWengine::Camera2D m_camera;
	BWengine::Camera2D m_hudCamera;

	BWengine::SpriteFont* m_spriteFont;

	BWengine::Window* m_window = nullptr;
	BWengine::InputManager* m_inputManager = nullptr;
	BWengine::AudioEngine* m_audioEngine = nullptr;
	World m_world;	

};

