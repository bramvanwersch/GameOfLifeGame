#include "Animation.h"


namespace BWengine {

	Animation::Animation(TextureSheet* textureSheet, const std::vector<int> textureIndexOrder,
		float framePlaySpeed, bool loop /*= true*/) {
		m_textureSheet = textureSheet;
		m_textureIndexOrder = textureIndexOrder;
		m_framePlaySpeed = framePlaySpeed;
		m_loop = loop;
	}

	Animation::~Animation()
	{
	}

	void Animation::update(float deltaTime)
	{
		if (finished) {
			return;
		}
		m_timeSinceLastIndex += deltaTime;
		if (m_timeSinceLastIndex >= m_framePlaySpeed) {
			m_timeSinceLastIndex -= m_framePlaySpeed;
			m_currentTextureIndex++;
			if (m_currentTextureIndex >= m_textureIndexOrder.size()) {
				if (m_loop) {
					m_currentTextureIndex = 0;
				}
				else {
					finished = true;
				}
			}
		}
	}

	void Animation::restart()
	{
		m_currentTextureIndex = 0;
		m_timeSinceLastIndex = 0;
		finished = false;
	}
}

