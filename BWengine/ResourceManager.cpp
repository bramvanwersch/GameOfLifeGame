#include "ResourceManager.h"


namespace BWengine {

	TextureCache ResourceManager::m_textureCache;


	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return m_textureCache.getTexture(texturePath);
	}

	void ResourceManager::addTextureSheet(std::string sheetPath, glm::ivec2 dims)
	{
		m_textureCache.addTextureSheet(sheetPath, dims);
	}

	TextureSheet* ResourceManager::getTextureSheet(std::string sheetPath) 
	{
		return m_textureCache.getTextureSheet(sheetPath);
	}
	
}