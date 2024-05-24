#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

#include "BWengineErrors.h"

namespace BWengine {

	TextureCache::TextureCache()
	{

	}

	TextureCache::~TextureCache()
	{

	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//std::map<std::string, GLTexture>::iterator
		auto mit = m_textureMap.find(texturePath);

		if (mit == m_textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			m_textureMap.insert(make_pair(texturePath, newTexture));
			return newTexture;
		}
		
		return mit->second;
	}

	void TextureCache::addTextureSheet(std::string sheetPath, glm::ivec2 dims) 
	{
		GLTexture texture = getTexture(sheetPath);

		TextureSheet newSheet;
		newSheet.init(texture, dims);
		m_sheetMap.insert(make_pair(sheetPath, newSheet));
	}

	TextureSheet* TextureCache::getTextureSheet(std::string sheetPath)
	{
		auto mit = m_sheetMap.find(sheetPath);

		if (mit == m_sheetMap.end()) {
			setLastError(ErrorCodes::UNLOADED_SHEET_ERROR, sheetPath);
			return nullptr;
		}

		return &mit->second;
	}
}