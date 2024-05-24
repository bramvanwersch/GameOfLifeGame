#include "Timing.h"

#include <SDL/SDL.h>

namespace BWengine{

	FpsLimiter::FpsLimiter()
	{

	}

	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		m_maxFPS = maxFPS;
	}

	void FpsLimiter::beginFrame()
	{
		m_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::endFrame()
	{
		calculateFPS();

		//limit fps to max fps
		Uint32 frameTicks = SDL_GetTicks() - m_startTicks;
		if (1000.0f / m_maxFPS > frameTicks) {
			SDL_Delay((Uint32) (1000.0f / m_maxFPS - frameTicks));
		}

		return m_fps;
	}

	void FpsLimiter::calculateFPS()
	{
		// global only accessible in this function
		static const int NUM_SAMPLES = 10;
		static unsigned int frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static Uint32 prevTicks = SDL_GetTicks();

		Uint32 currentTicks;
		currentTicks = SDL_GetTicks();

		m_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		int count;
		currentFrame++;

		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0) {
			m_fps = 1000.0f / frameTimeAverage;
		}
		else {
			m_fps = 60.0f;
		}
	}
}