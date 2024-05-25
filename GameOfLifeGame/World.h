#pragma once
#include <vector>
#include <random>
#include <memory>

#include <BWengine/Camera2D.h>
#include <BWengine/InputManager.h>
#include <BWengine/TextureSheet.h>
#include <BWengine/ResourceManager.h>
#include <BWengine/SpriteBatch.h>

#include "utility.h"
#include "Constants.h"
#include "GameTexture.h"
#include "Block.h"
#include "BlockTypeLibrary.h"


class World
{
public:

	World();
	~World();

	void update(BWengine::InputManager* inputManager, BWengine::Camera2D& camera);
	void processInput(BWengine::InputManager* inputManager, BWengine::Camera2D& camera);
	
	void draw(BWengine::Camera2D& camera);
	void generate();

	//getters
	int getUpdatedBlocks() { return (int) (m_updatedBlocks.getAverage() + 0.5f); }
	int getTotalBlocks() { return (int)(m_totalBlocks.getAverage() + 0.5f); }

	float getUpdateTime() { return m_updateTime.getAverage(); }
	float getUpdateBlockTime() { return m_updateBlockTime.getAverage(); }
	float getUpdateMoveTime() { return m_movementTime.getAverage(); }
	float getUpdateDrawTime() { return m_drawTime.getAverage(); }

protected:

	void updateBlocks();
	void setBlock(glm::vec2 worldPosition);
	int coordToIndex(int x, int y);
	Block* getBlockAtCoord(int x, int y);
	void setBlockAtCoord(int x, int y, BlockType* type);

	//variables
	BWengine::SpriteBatch m_spriteBatch;  // for drawing background
	std::unique_ptr<BlockTypeLibrary> m_blockTypeLibrary = nullptr;

	std::unique_ptr<GameTexture> m_backgroundTexture = nullptr;
	AverageCollection m_updatedBlocks;
	AverageCollection m_totalBlocks;

	// time execution
	AverageCollection m_updateTime;
	AverageCollection m_movementTime;
	AverageCollection m_updateBlockTime;
	AverageCollection m_drawTime;

	float m_previousTicks = (float)SDL_GetTicks();

	std::array<Block*, NR_BLOCKS_WIDTH * NR_BLOCKS_HEIGTH> m_blocks = {nullptr};

	bool m_paused = false;

};