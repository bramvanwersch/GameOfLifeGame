#include "GamePLayScreen.h"

#include <iostream>
#include <SDL/SDL.h>
#include <random>

#include <BWengine/IMainGame.h>
#include <BWengine/ResourceManager.h>
#include <BWengine/BWengineErrors.h>

#include "Constants.h"


GamePlayScreen::GamePlayScreen(BWengine::Window* window, BWengine::InputManager* inputManager,
	BWengine::AudioEngine* audioEngine) :
	m_window(window),
	m_inputManager(inputManager),
	m_audioEngine(audioEngine),
	m_world()
{
}

GamePlayScreen::~GamePlayScreen()
{
}

int GamePlayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GamePlayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GamePlayScreen::build()
{
}

void GamePlayScreen::destroy()
{
}

void GamePlayScreen::onEntry()
{

	// add textures
	BWengine::ResourceManager::addTextureSheet("textures/blank.png", glm::vec2(1, 1));

	//init batch
	m_hudSpriteBatch.init();

	// Initialize sprite font
	m_spriteFont = new BWengine::SpriteFont("Fonts/manaspc.ttf", 32);

	if (!m_textureProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag")) {
		BWengine::raiseLastError(); // quits the game
	}
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	if (!m_textureProgram.linkShaders()) {
		BWengine::raiseLastError(); // quits the game
	}

	//camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setPosition((glm::vec2(PIXEL_WIDTH, PIXEL_HEIGTH) / glm::vec2(2, 2)));
	m_camera.setScale(DEFAULT_ZOOM);
	m_hudCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_hudCamera.setPosition(glm::vec2(m_window->getScreenWidth() / 2, m_window->getScreenHeight() / 2));
	m_world.generate();
}

void GamePlayScreen::onExit()
{
	delete m_spriteFont;
}

void GamePlayScreen::update()
{
	checkInput();
	if (m_currentState != BWengine::ScreenState::RUNNING) {
		return;
	}

	updateCameraPosition();
	m_camera.update();
	m_hudCamera.update();
	m_world.update(m_inputManager, m_camera);
}

void GamePlayScreen::updateCameraPosition()
{
	glm::vec2 deltaMove = { 0.0f, 0.0f };
	if (m_inputManager->isKeyDown(BWengine::Keys::left)) {
		deltaMove.x -= CAMERA_SPEEDX;
	}
	if (m_inputManager->isKeyDown(BWengine::Keys::rigth)) {
		deltaMove.x += CAMERA_SPEEDX;
	}
	if (m_inputManager->isKeyDown(BWengine::Keys::up)) {
		deltaMove.y += CAMERA_SPEEDX;
	}
	if (m_inputManager->isKeyDown(BWengine::Keys::down)) {
		deltaMove.y -= CAMERA_SPEEDX;
	}
	m_camera.movePosition(deltaMove);
}

void GamePlayScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}

	// allow scrolling to zoom
	glm::vec2 scrolled = m_inputManager->getScrolled();

	float new_scale = m_camera.getScale() + scrolled.y;
	if (new_scale < MIN_ZOOM) {
		new_scale = MIN_ZOOM;
	}
	else if (new_scale > MAX_ZOOM) {
		new_scale = MAX_ZOOM;
	}
	m_camera.setScale(new_scale);
}

void GamePlayScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_textureProgram.use();

	GLuint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLuint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_world.draw(m_camera);

	drawHud();

	m_textureProgram.unuse();
}


void GamePlayScreen::drawHud() {
	char buffer[512];

	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_hudSpriteBatch.begin();
	std::string blockName;
	sprintf_s(buffer, "FPS: %.0f\nZ: %.0f\nCh l: %d\nl: %d / %d\nBlock:\nn: %s\n\nTiming:\nUpdate: %.1f\n  b: %.1f\n  m: %.1f\nDraw: %.1f",
		m_fps, m_camera.getScale(), m_world.getLoadedChunks(), m_world.getUpdatedBlocks(), m_world.getTotalBlocks(), blockName.c_str(),
		m_world.getUpdateTime(), m_world.getUpdateBlockTime(), m_world.getUpdateMoveTime(), m_world.getUpdateDrawTime());
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, m_window->getScreenHeight() - m_spriteFont->getFontHeight()),
		glm::vec2(1.0f / 2.0f), 0.0f, BWengine::ColorRGBA8(150, 150, 150, 255));

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}