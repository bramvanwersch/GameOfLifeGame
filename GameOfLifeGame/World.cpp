#include "World.h"
#include <BWengine/BWengineErrors.h>

World::World()
{
	m_spriteBatch.init();
}

World::~World()
{
}

void World::generate() {
	m_blockTypeLibrary = std::make_unique<BlockTypeLibrary>();
	BWengine::TextureSheet* sheet = BWengine::ResourceManager::getTextureSheet("textures/blank.png");
	if (sheet == nullptr) {
		BWengine::raiseLastError();
	}
	m_backgroundTexture = std::make_unique<GameTexture>();
	m_backgroundTexture->init(glm::vec2(PIXEL_WIDTH, PIXEL_HEIGTH),
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

void World::setBlock(glm::vec2 worldPosition) {
	// set a number of blocks based on the size chosen by user
	worldPosition = glm::floor(worldPosition);
	int x = (int) (worldPosition[0] / BLOCK_WIDTH);
	int y = NR_BLOCKS_HEIGTH - 1 - (int) (worldPosition[1] / BLOCK_HEIGTH);
	std::string name = "test";
	setBlockAtCoord(x, y, m_blockTypeLibrary->getBlockType(&name));
}

Block* World::getBlockAtCoord(int x, int y) {
	if (!isCoordValid(x, y)) {
		return nullptr;
	}
	std::string key = coordToKey(x, y);
	 auto it = m_blocks.find(key);
	 if (it == m_blocks.end()) {
		 return nullptr;
	 }
	 return it->second;
}

void World::setBlockAtCoord(int x, int y, BlockType* type) {
	if (!isCoordValid(x, y)) {
		return;
	}
	std::string key = coordToKey(x, y);
	m_blocks.insert(std::make_pair(key, new Block(type, { x * BLOCK_WIDTH, (NR_BLOCKS_HEIGTH - 1 - y) * BLOCK_HEIGTH })));
}

bool World::isCoordValid(int x, int y) {
	if (x < 0 || y < 0) {
		return false;
	}
	if (x >= NR_BLOCKS_WIDTH || y >= NR_BLOCKS_HEIGTH) {
		return false;
	}
	return true;
}

std::string World::coordToKey(int x, int y) {
	return string_format("%d,%d", x, y);
}


void World::processInput(BWengine::InputManager* inputManager, BWengine::Camera2D& camera)
{
	if (inputManager->isKeyDown(BWengine::Keys::mouse_left)) {
		glm::vec2 worldPosition = inputManager->getMouseCoords();
		worldPosition = camera.screenToWorldCoords(worldPosition);
		setBlock(worldPosition);
	}

	if (inputManager->isKeyPressed(BWengine::Keys::space)) {
		m_paused = !m_paused;
		//make sure time is not skipped
		m_previousTicks = (float)SDL_GetTicks();
	}
}

void World::draw(BWengine::Camera2D& camera)
{
	float beforeTimeValue = (float)SDL_GetTicks();
	const glm::vec4 worldRect(0.0f, 0.0f, PIXEL_WIDTH, PIXEL_HEIGTH);
	//draw background
	m_spriteBatch.begin();
	m_spriteBatch.draw(worldRect, m_backgroundTexture->getUVs(), m_backgroundTexture->texture->id, 0.0f,
		m_backgroundTexture->color);
	// not fantastic
	for (auto kv : m_blocks) {
		Block* block = kv.second;
		BlockType* type = block->getType();
		glm::vec2* position = block->getPosition();
		m_spriteBatch.draw({position->x, position->y, BLOCK_WIDTH, BLOCK_HEIGTH}, type->getUVs(), type->getTextureID(), 0.0f,
			type->getColor());
	}
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_drawTime.add((float)SDL_GetTicks() - beforeTimeValue);
}
