#include "Constants.h"
#include "World.h"
#include <BWengine/BWengineErrors.h>

World::World(glm::vec2 size)
{
	m_size = size; // in chunks
	m_spriteBatch.init();

}

World::~World()
{
}

void World::generate() {
	BWengine::TextureSheet* sheet = BWengine::ResourceManager::getTextureSheet("textures/blank.png");
	if (sheet == nullptr) {
		BWengine::raiseLastError();
	}
	m_backgroundTexture = std::make_unique<GameTexture>();
	m_backgroundTexture->init(m_size * glm::vec2(CHUNK_WIDTH * BLOCK_WIDTH, CHUNK_HEIGTH * BLOCK_HEIGTH),
	BWengine::ColorRGBA8(255, 255, 255, 255), sheet);
}

void World::update(BWengine::InputManager* inputManager, BWengine::Camera2D& camera)
{
	float beforeTimeValue = (float)SDL_GetTicks();
	//update inputs and blocks
	processInput(inputManager, camera);
	if (!m_paused) {
		updateBlocks();
	}
	m_updateTime.add((float)SDL_GetTicks() - beforeTimeValue);

}

void World::updateBlocks(){

}

void World::processInput(BWengine::InputManager* inputManager, BWengine::Camera2D& camera)
{
	if (inputManager->isKeyDown(BWengine::Keys::mouse_left)) {
		glm::vec2 worldPosition = inputManager->getMouseCoords();
		worldPosition = camera.screenToWorldCoords(worldPosition);
	}
	else if (inputManager->isKeyDown(BWengine::Keys::mouse_right)) {
		glm::vec2 worldPosition = inputManager->getMouseCoords();
		worldPosition = camera.screenToWorldCoords(worldPosition);
		std::string voidName = "void";
	}

	if (inputManager->isKeyPressed(BWengine::Keys::space)) {
		m_paused = !m_paused;
		//make sure time is not skipped
		m_previousTicks = (float)SDL_GetTicks();
	}

	if (inputManager->isKeyPressed(BWengine::Keys::equals) || inputManager->isKeyPressed(BWengine::Keys::plus_np)) {
		if (m_blocksPlacedIndex < MAX_INDEX) {
			m_blocksPlacedIndex++;
		}
	}
	else if (inputManager->isKeyPressed(BWengine::Keys::minus) || inputManager->isKeyPressed(BWengine::Keys::minus_np)) {
		if (m_blocksPlacedIndex > 0) {
			m_blocksPlacedIndex--;
		}
	}
}

void World::draw(BWengine::Camera2D& camera)
{
	float beforeTimeValue = (float)SDL_GetTicks();
	const glm::vec4 worldRect(0.0f, 0.0f, m_size.x * CHUNK_WIDTH * BLOCK_WIDTH, m_size.y * CHUNK_HEIGTH * BLOCK_HEIGTH);
	//draw background
	m_spriteBatch.begin();
	m_spriteBatch.draw(worldRect, m_backgroundTexture->getUVs(), m_backgroundTexture->texture->id, 0.0f,
		m_backgroundTexture->color);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_drawTime.add((float)SDL_GetTicks() - beforeTimeValue);
}

bool World::isValidWorldPositon(glm::vec2& position)
{
	if (position.x < 0 || position.x >= m_size.x * CHUNK_WIDTH * BLOCK_WIDTH) {
		return false;
	}
	if (position.y < 0 || position.y >= m_size.y * CHUNK_HEIGTH * BLOCK_HEIGTH) {
		return false;
	}
	return true;
}

size_t World::worldPositionToIndex(glm::vec2 worldPosition)
{
	const glm::vec2 pixelChunkSize = { CHUNK_WIDTH * BLOCK_WIDTH, CHUNK_HEIGTH * BLOCK_HEIGTH };
	glm::vec2 chunkPos = glm::floor(worldPosition / pixelChunkSize);
	return (size_t)(chunkPos.x + chunkPos.y * m_size.x);
}
