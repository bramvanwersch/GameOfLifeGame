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
	int index = coordToIndex(x, y);
	return m_blocks[index];
}

void World::setBlockAtCoord(int x, int y, BlockType* type) {
	int index = coordToIndex(x, y);
	if (index < 0) {
		return;
	}
	m_blocks[index] = new Block(type);
}

int World::coordToIndex(int x, int y) {
	if (x < 0 || y < 0) {
		return -1;
	}
	if (x >= NR_BLOCKS_WIDTH || y >= NR_BLOCKS_HEIGTH) {
		return -1;
	}
	int index = y * NR_BLOCKS_WIDTH + x;
	return index;
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
	for (int i = 0; i < m_blocks.size(); i++) {
		Block* block = m_blocks[i];
		if (block != nullptr) {
			BlockType* type = block->getType();
			m_spriteBatch.draw({(i % NR_BLOCKS_WIDTH) * BLOCK_WIDTH, (NR_BLOCKS_HEIGTH - 1 - (i / NR_BLOCKS_WIDTH)) * BLOCK_HEIGTH, BLOCK_WIDTH, BLOCK_HEIGTH}, type->getUVs(), type->getTextureID(), 0.0f,
				type->getColor());
		}
	}
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_drawTime.add((float)SDL_GetTicks() - beforeTimeValue);
}
