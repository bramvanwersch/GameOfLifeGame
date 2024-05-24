#pragma once

#include "GLTexture.h"
#include <string>


namespace BWengine {

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}
