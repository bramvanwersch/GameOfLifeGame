#include "Camera2D.h"

#include <iostream>

namespace BWengine {

	Camera2D::Camera2D() :
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_needsMatrixUpdate(true),
		m_screenWidth(100),
		m_screenHeight(100)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::init(int screenWidth, int screenHeight) {
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth,
			0.0f, (float)m_screenHeight);

	}

	void Camera2D::update()
	{
		if (m_needsMatrixUpdate) {
			//camera translation
			glm::vec3 translate(-m_position.x + m_screenWidth / 2,
				-m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			//camera scaling
			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			
			m_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::screenToWorldCoords(glm::vec2 screenCoord)
	{
		//ivert y
		screenCoord.y = m_screenHeight - screenCoord.y;

		//make 0,0 center
		screenCoord -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);

		//scale coords
		screenCoord /= m_scale;

		//translate coords
		screenCoord += m_position;
		return screenCoord;
	}

	bool Camera2D::inView(const glm::vec2 position, const glm::vec2 dimensions) {

		glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scale);

		// The minimum distance before a collision occurs
		const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

		// Center position of the parameters
		glm::vec2 centerPos = position + dimensions / 2.0f;
		// Center position of the camera
		glm::vec2 centerCameraPos = m_position;
		// Vector from the input to the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		// Get the depth of the collision
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		// If both the depths are > 0, then we collided
		if (xDepth > 0 && yDepth > 0) {
			// There was a collision
			return true;
		}
		return false;
	}
}