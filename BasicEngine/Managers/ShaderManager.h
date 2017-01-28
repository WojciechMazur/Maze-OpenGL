#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
namespace BasicEngine {
	namespace Managers
	{

		class ShaderManager
		{
		public:
			ShaderManager();
			~ShaderManager();

			void CreateProgram(const std::string& shaderName,
				const std::string& vertexShaderFilename,
				const std::string& fragmentShaderFilename);

			static const GLuint GetShader(const std::string&);

		private:
			std::string ReadShader(const std::string& filename);
			GLuint CreateShader(GLenum shaderType,
				const std::string& source,
				const std::string& shaderName);

			static std::map<std::string, GLuint> programs;
		};

	}
}