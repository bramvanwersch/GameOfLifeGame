#pragma once

#include <map>
#include <string>

#include "GLTexture.h"
#include "TextureSheet.h"

namespace BWengine {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

		void addTextureSheet(std::string sheetPath, glm::ivec2 dims);
		TextureSheet* getTextureSheet(std::string sheetPath);

	private:
		std::map<std::string, GLTexture> m_textureMap;
		std::map<std::string, TextureSheet> m_sheetMap;
	};

}