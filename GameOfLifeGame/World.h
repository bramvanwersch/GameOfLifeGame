#pragma once
#include <vector>
#include <random>

#include <BWengine/Camera2D.h>
#include <BWengine/InputManager.h>
#include <BWengine/TextureSheet.h>
#include <BWengine/ResourceManager.h>

#include "utility.h"
#include <BWengine/SpriteBatch.h>
#include <memory>
#include "GameTexture.h"
#include <map>


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
	int getLoadedChunks() { return m_loadedChunks; }
	int getUpdatedBlocks() { return (int) (m_updatedBlocks.getAverage() + 0.5f); }
	int getTotalBlocks() { return (int)(m_totalBlocks.getAverage() + 0.5f); }

	float getUpdateTime() { return m_updateTime.getAverage(); }
	float getUpdateBlockTime() { return m_updateBlockTime.getAverage(); }
	float getUpdateMoveTime() { return m_movementTime.getAverage(); }
	float getUpdateDrawTime() { return m_drawTime.getAverage(); }

protected:

	void updateBlocks();
	void setBlock(glm::vec2 worldPosition);

	//variables
	BWengine::SpriteBatch m_spriteBatch;  // for drawing background
	std::unique_ptr<GameTexture> m_backgroundTexture = nullptr;
	int m_loadedChunks = 0;
	AverageCollection m_updatedBlocks;
	AverageCollection m_totalBlocks;

	// time execution
	AverageCollection m_updateTime;
	AverageCollection m_movementTime;
	AverageCollection m_updateBlockTime;
	AverageCollection m_drawTime;

	float m_previousTicks = (float)SDL_GetTicks();

	std::map<int, std::map<int, std::string>> blocks;

	bool m_paused = false;

};