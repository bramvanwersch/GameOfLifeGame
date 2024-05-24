#include "GLSLProgram.h"

#include <fstream>
#include <vector>
#include <iostream>

#include "BWengineErrors.h"
#include "IOManager.h"

namespace BWengine {

	GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
		dispose();
	}


	bool GLSLProgram::compileShaders(const std::string& vertexShaderFilePath,
		const std::string& fragmentShaderFilePath)
	{

		std::string vertSource;
		std::string fragSource;

		if (!IOManager::readFileToBuffer(vertexShaderFilePath, vertSource)) {
			setLastError(ErrorCodes::READ_FILE_ERROR, vertexShaderFilePath);
			return false;
		}
		if (!IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource)) {
			setLastError(ErrorCodes::READ_FILE_ERROR, fragmentShaderFilePath);
			return false;
		}

		return compileShadersFromSource(vertSource.c_str(), fragSource.c_str(), vertexShaderFilePath, fragmentShaderFilePath);
	}

	bool GLSLProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource,
		const std::string vertexId, const std::string fragmentId)
	{
		// allow to pas in ID's that can identify what shader does not compile
		m_programID = glCreateProgram();

		m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertexShaderID == 0) {
			setLastError(ErrorCodes::SHADER_CREATION_ERROR, "Vertex");
			return false;
		}

		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragmentShaderID == 0) {
			setLastError(ErrorCodes::SHADER_CREATION_ERROR, "Fragment");
			return false;
		}

		return compileShader(vertexSource, m_vertexShaderID, vertexId) && 
			compileShader(fragmentSource, m_fragmentShaderID, fragmentId);
	}


	bool GLSLProgram::compileShader(const char* source, GLuint id, const std::string fileId)
	{

		glShaderSource(id, 1, &source, nullptr);

		glCompileShader(id);

		GLint succes = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &succes);

		if (succes == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.

			setLastError(ErrorCodes::SHADER_CREATION_ERROR, fileId + " failed with log: " + std::string(&errorLog[0]));
			return false;

		}
		return true;
	}

	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(m_programID, m_numAttributes, attributeName.c_str());
		m_numAttributes++;
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			setLastError(ErrorCodes::MISSING_SHADER_UNIFORM_ERROR, uniformName);
			fatalError(getLastError());
		}
		return location;
	}

	void GLSLProgram::use()
	{
		glUseProgram(m_programID);
		for (int i = 0; i < m_numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < m_numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::dispose() {
		if (m_programID) {
			glDeleteProgram(m_programID);
		}
		
	}

	bool GLSLProgram::linkShaders()
	{

		// Attach our shaders to our program
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);

		// Link our program
		glLinkProgram(m_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_programID);
			// Don't leak shaders either.
			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);

			setLastError(ErrorCodes::SHADER_LINK_ERROR, std::string(&errorLog[0]));
			return false;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);
		return true;
	}

}