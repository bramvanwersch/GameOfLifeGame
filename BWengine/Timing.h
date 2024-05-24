#pragma once

namespace BWengine {

	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);
		
		void beginFrame();
		float endFrame();

	private:
		float m_maxFPS;
		unsigned int m_startTicks;

		float m_fps;
		unsigned int m_frameTime;


		void calculateFPS();
	};
}