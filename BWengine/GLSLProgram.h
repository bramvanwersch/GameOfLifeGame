#pragma once

#include <GL/glew.h>
#include <string>

namespace BWengine {


	//open gl pragramming language program
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		bool compileShaders(const std::string& vertexShaderFilePath,
			const std::string& fragmentShaderFilePath);

		bool compileShadersFromSource(const char* vertexSource, const char* fragmentSource,
			const std::string vertexId, const std::string fragmentId);

		bool linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

		void dispose();

	private:

		int m_numAttributes;

		bool compileShader(const char* source, GLuint id, const std::string type);

		GLuint m_programID;

		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
	};

}