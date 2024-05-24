#pragma once
#include <array>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace BWengine {


	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 screenToWorldCoords(glm::vec2 screenCoord);

		//bool collideWithRect(Rect* rect);

		//setters
		void setPosition(glm::vec2 newPosition) {
			m_position = newPosition;
			m_needsMatrixUpdate = true;
		}

		void movePosition(glm::vec2 delta) {
			m_position += delta;
			m_needsMatrixUpdate = true;
		}

		void setPosition(std::array<int, 2> newPosition) {
			m_position.x = (float) newPosition[0];
			m_position.y = (float) newPosition[1];
			m_needsMatrixUpdate = true; 
		}
		void setScale(float newScale) { m_scale = newScale; m_needsMatrixUpdate = true; }
		bool inView(glm::vec2 position, glm::vec2 dimension);

		//getters
		glm::vec2 getPosition() { return m_position; }
		float getScale() { return m_scale; }
		glm::mat4 getCameraMatrix() { return m_cameraMatrix; }

	private:
		int m_screenWidth;
		int m_screenHeight;

		bool m_needsMatrixUpdate;
		float m_scale;

		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;

	};

}