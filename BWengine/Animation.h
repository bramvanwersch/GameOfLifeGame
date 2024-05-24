#pragma once

#include <vector>

#include "TextureSheet.h"

namespace BWengine {
	class Animation
	{
	public:
		Animation() {}
		Animation(TextureSheet* textureSheet, const std::vector<int> textureIndexOrder,
			float framePlaySpeed, bool loop = true);
		~Animation();

		void update(float deltaTime);

		void restart();

		GLuint getId() { return m_textureSheet->id; }
		int getTextureIndex() { return m_textureIndexOrder[m_currentTextureIndex]; }

		bool finished = false;

	private:
		TextureSheet* m_textureSheet = nullptr;
		std::vector<int> m_textureIndexOrder;
		unsigned int m_currentTextureIndex = 0;
		float m_framePlaySpeed;
		float m_timeSinceLastIndex = 0.0f;
		bool m_loop;
	};

}

