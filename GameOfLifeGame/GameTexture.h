#pragma once

#include <BWengine/TextureSheet.h>
#include <BWengine/colors.h>

typedef struct GameTexture
{
	void init(const glm::vec2& dim, BWengine::ColorRGBA8 color,
		BWengine::TextureSheet* textureSheet)
	{
		this->textureDimensions = dim;
		this->color = color;
		this->texture = textureSheet;
	}
	glm::vec4 getUVs() {
		return texture->getUVs(textureIndex, flipTexture[0], flipTexture[1]);
	}
	int textureIndex = 0; //index of the texture on the TileSheet
	BWengine::TextureSheet* texture;
	BWengine::ColorRGBA8 color;

	glm::vec2 textureDimensions;
	bool flipTexture[2] = { false, false }; // flip texture x, y
} GameTexture;

