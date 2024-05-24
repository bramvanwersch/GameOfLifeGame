#pragma once

#include <glm/glm.hpp>

#include "GLTexture.h"


namespace BWengine {
	class TextureSheet {
	public:
		void init(const GLTexture& texture, glm::ivec2& tileDims) {
			this->m_texture = texture;
			this->id = texture.id;
			this->dims = tileDims;
		}

		glm::vec4 getUVs(int index, bool flipX=false, bool flipY=false) {
			int xTile = index % dims.x;
			int yTile = dims.y - index / dims.x -1;

			glm::vec4 uvs;
			if (flipX) {
				uvs.x = xTile / (float)dims.x + 1.0f / dims.x;
			}
			else {
				uvs.x = xTile / (float)dims.x;
			}
			
			if (flipY) {
				uvs.y = yTile / (float)dims.y + 1.0f / dims.y;
			}
			else {
				uvs.y = yTile / (float)dims.y;
			}
			if (flipX) {
				uvs.z = -1.0f / dims.x;
			}
			else {
				uvs.z = 1.0f / dims.x;
			}
			if (flipY) {
				uvs.w = -1.0f / dims.y;
			}
			else {
				uvs.w = 1.0f / dims.y;
			}
			return uvs;
		}

		GLuint id;
		glm::ivec2 dims;

		GLTexture& getTexture() { return m_texture; }

	private:
		GLTexture m_texture;
	};
}
