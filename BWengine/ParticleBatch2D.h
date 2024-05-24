#pragma once

#include <glm/glm.hpp>
#include <functional>

#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

namespace BWengine {

	class Particle2D {
	public:
		glm::vec2 position = glm::vec2(0, 0);
		glm::vec2 velocity = glm::vec2(0, 0);
		ColorRGBA8 color;
		float lifeTime = 0.0f;
		float width = 0.0f;
	};

	inline void deafultParticleUpdate(Particle2D& p, float deltaTime) {
		p.position += p.velocity * deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles, float decayRate, GLTexture texture,
			std::function<void(Particle2D&, float)> updateFunc = deafultParticleUpdate);

		void addParticle(const glm::vec2& position, 
			const glm::vec2& velocity,
			const ColorRGBA8& color, 
			float width);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

	private:
		int findFreeParticle();

		std::function<void(Particle2D&, float)> m_updateFunc;

		float m_decayRate;
		//buffer, is way more efficient with repeated loops
		Particle2D* m_particles = nullptr;
		int m_maxParticles = 0;
		int m_lastFreeParticle = 0;
		GLTexture m_texture;

	};
}


