#pragma once
#include "TextureCache.h"

#include<string>


namespace BWengine {


	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

		static void addTextureSheet(std::string sheetPath, glm::ivec2 dims);
		static TextureSheet* getTextureSheet(std::string sheetPath);

	private:
		static TextureCache m_textureCache;
	};

}