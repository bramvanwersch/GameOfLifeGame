#pragma once

#include <memory>

#include <BWengine/TextureSheet.h>
#include <BWengine/colors.h>

#include "Constants.h"
#include <GameOfLifeGame/GameTexture.h>
#include <BWengine/ResourceManager.h>
#include <BWengine/BWengineErrors.h>


class BlockType {

public:

	BlockType(BWengine::ColorRGBA8 color) {
		m_texture = std::make_unique<GameTexture>();
		BWengine::TextureSheet* sheet = BWengine::ResourceManager::getTextureSheet("textures/blank.png");
		if (sheet == nullptr) {
			BWengine::raiseLastError();
		}
		m_texture->init(m_dim, color, sheet);
	};

	glm::vec2& getTextureDimensions() { return m_dim; }
	glm::vec4 getUVs() { return m_texture->getUVs(); }
	GLuint getTextureID() { return m_texture->texture->id; }
	BWengine::ColorRGBA8& getColor() { return m_texture->color; }

protected:
	glm::vec2 m_dim = glm::vec2(BLOCK_WIDTH, BLOCK_HEIGTH);
	std::unique_ptr<GameTexture> m_texture = nullptr;
};
