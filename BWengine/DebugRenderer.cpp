#include "DebugRenderer.h"

#include <iostream>

#include "BWengineErrors.h"


#define PI 3.14159265358979323846f

// basic shaders
namespace {/// prevent name collission
	const char* VERT_SRC = R"(#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;

out vec2 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 P;

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	//the z position is zero since we are in 2D
	gl_Position.z = 0.0;
    
	//Indicate that the coordinates are normalized
	gl_Position.w = 1.0;
    
	fragmentPosition = vertexPosition;
    
	fragmentColor = vertexColor;
})";

	const char* FRAG_SRC = R"(#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

void main() {

	color = fragmentColor;
})";
}


namespace BWengine {
	DebugRenderer::DebugRenderer()
	{
		//empty
	}

	DebugRenderer::~DebugRenderer()
	{
		dispose();
	}

	void DebugRenderer::init()
	{
		//shader init
		if (!m_program.compileShadersFromSource(VERT_SRC, FRAG_SRC,
			"Debug Renderer Vertex shader", "Debug Renderer Fragment shader")) {
			raiseLastError(); // safety quit
		}
		m_program.addAttribute("vertexPosition");
		m_program.addAttribute("vertexColor");
		if (!m_program.linkShaders()) {
			raiseLastError(); // safety quit
		}

		// Set up buffers
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

		glBindVertexArray(0);
	}

	void DebugRenderer::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(DebugVertex), m_vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		// Orphan the buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_numElements = m_indices.size();
		m_indices.clear();
		m_vertices.clear();
	}

	glm::vec2 rotatePoint(glm::vec2 pos, float angle) {
		glm::vec2 newPos;
		newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
		newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newPos;
	}

	void DebugRenderer::drawBox(const glm::vec4& destRect, const ColorRGBA8 color, float angle)
	{
		int i = m_vertices.size();
		m_vertices.resize(m_vertices.size() + 4);

		glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		// Get points centered at origin
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		glm::vec2 positionOffset(destRect.x, destRect.y);

		// Rotate the points
		m_vertices[i].position = rotatePoint(tl, angle) + halfDims + positionOffset;
		m_vertices[i + 1].position = rotatePoint(bl, angle) + halfDims + positionOffset;
		m_vertices[i + 2].position = rotatePoint(br, angle) + halfDims + positionOffset;
		m_vertices[i + 3].position = rotatePoint(tr, angle) + halfDims + positionOffset;

		for (int j = i; j < i + 4; j++) {
			m_vertices[j].color = color;
		}

		m_indices.reserve(m_indices.size() + 8);

		m_indices.push_back(i);
		m_indices.push_back(i + 1);

		m_indices.push_back(i + 1);
		m_indices.push_back(i + 2);

		m_indices.push_back(i + 2);
		m_indices.push_back(i + 3);

		m_indices.push_back(i + 3);
		m_indices.push_back(i);
	}

	void DebugRenderer::drawCircle(const glm::vec2& center, const ColorRGBA8 color, float radius)
	{
		// PI / \arccos(1 - 0.5 / x) --> function for getting the number of vertices needed with an error of 0.5
		// 10 + 0.2x --> approximate of the above function --> faster calculation
		int numVerts = (int) (10 + 0.2f * radius);

		int start = m_vertices.size();

		m_vertices.resize(m_vertices.size() + numVerts);
		for (int i = 0; i < numVerts; i++) {
			// angle in radians
			float angle = ((float)i / numVerts) * PI * 2.0f;
			m_vertices[start + i].position.x = cos(angle) * radius + center.x;
			m_vertices[start + i].position.y = sin(angle) * radius + center.y;
			m_vertices[start + i].color = color;
		}

		m_indices.reserve(m_indices.size() + numVerts * 2);
		for (int i = 0; i < numVerts - 1; i++) {
			m_indices.push_back(start + i);
			m_indices.push_back(start + i + 1);
		}

		m_indices.push_back(start + numVerts - 1);
		m_indices.push_back(start);
	}

	void DebugRenderer::render(const glm::mat4& projectionMatrix, float lineWidth)
	{
		m_program.use();

		GLint pUniform = m_program.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		glLineWidth(lineWidth);
		glBindVertexArray(m_vao);
		glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		m_program.unuse();
	}

	void DebugRenderer::dispose()
	{
		if (m_vao) {
			glDeleteVertexArrays(1, &m_vao);
		}
		if (m_vbo) {
			glDeleteBuffers(1, &m_vbo);
		}
		if (m_ibo) {
			glDeleteBuffers(1, &m_ibo);
		}
		m_program.dispose();
	}

}
