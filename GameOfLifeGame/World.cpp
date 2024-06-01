#include "World.h"
#include <BWengine/BWengineErrors.h>
#include <iostream>

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
	if (!m_paused) {
		updateBlocks();
	}
	//update inputs and blocks
	processInput(inputManager, camera);

	m_updateTime.add((float)SDL_GetTicks() - beforeTimeValue);

}

void World::updateBlocks(){
	std::vector<std::shared_ptr<Block>> new_blocks;
	std::vector<std::string> remove_keys;
	for (auto kv : m_blocks) {
		Block* block = kv.second.get();
		block->update();
		new_blocks.push_back(kv.second);
		remove_keys.push_back(kv.first);
	}
	// not the geatest solution, might be a way better way
	for (std::string key : remove_keys) {
		removeBlock(&key);
	}
	for (std::shared_ptr<Block> block : new_blocks) {
		setBlock(block);
	}
}

void World::setBlockAtMouse(glm::vec2 worldPosition, BlockType* type) {
	worldPosition = glm::floor(worldPosition);
	int x = (int) (worldPosition[0] / BLOCK_WIDTH);
	int y = NR_BLOCKS_HEIGTH - 1 - (int) (worldPosition[1] / BLOCK_HEIGTH);
	setBlockTypeAtCoord(x, y, type);
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
	 return it->second.get();
}

void World::setBlock(std::shared_ptr<Block> block) {
	glm::vec2* position = block.get()->getPosition();
	if (!isPositionValid(position->x, position->y)) {
		return;
	}
	std::array<int, 2> coord = block.get()->getCoord();
	std::string key = coordToKey(coord[0], coord[1]);
	m_blocks.emplace(std::make_pair(key, block));
}

void World::setBlockTypeAtCoord(int x, int y, BlockType* type) {
	if (!isCoordValid(x, y)) {
		return;
	}
	std::string key = coordToKey(x, y);
	if (type == nullptr) {
		removeBlock(&key);
	}
	else {
		m_blocks.emplace(std::make_pair(key, std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(type, { x * BLOCK_WIDTH, (NR_BLOCKS_HEIGTH - 1 - y) * BLOCK_HEIGTH }))));
	}
}

void World::removeBlock(std::string* key){
	auto it = m_blocks.find(*key);
	if (it == m_blocks.end()){
		return;
	}
	m_blocks.erase(it);
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

bool World::isPositionValid(float x, float y) {
	if (x < 0 || y < 0) {
		return false;
	}
	// because block coordinate is bottom left
	if (x >= NR_BLOCKS_WIDTH * BLOCK_WIDTH || y >= NR_BLOCKS_HEIGTH * BLOCK_HEIGTH) {
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
		std::string type_name = "directional_spreader";
		BlockType* type = m_blockTypeLibrary->getBlockType(&type_name);
		setBlockAtMouse(worldPosition, type);
	}
	if (inputManager->isKeyDown(BWengine::Keys::mouse_right)) {
		glm::vec2 worldPosition = inputManager->getMouseCoords();
		worldPosition = camera.screenToWorldCoords(worldPosition);
		setBlockAtMouse(worldPosition, nullptr);
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
		Block* block = kv.second.get();
		BlockType* type = block->getType();
		glm::vec2* position = block->getPosition();
		m_spriteBatch.draw({position->x, position->y, BLOCK_WIDTH, BLOCK_HEIGTH}, type->getUVs(), type->getTextureID(), 0.0f,
			type->getColor());
	}
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_drawTime.add((float)SDL_GetTicks() - beforeTimeValue);
}
