#include "ShaderManager.h"


using namespace BasicEngine::Managers;

std::map<std::string, GLuint> ShaderManager::programs;

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint currentProgram = i->second;
		glDeleteProgram(currentProgram);
	}
	programs.clear();
}

void BasicEngine::Managers::ShaderManager::CreateProgram(const std::string & shaderName, const std::string & vertexShaderFilename, const std::string & fragmentShaderFilename)
{
	std::string vertexShaderCode = ReadShader(vertexShaderFilename);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "Vertex shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "Fragment shader");

	GLint linkingSuccess;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkingSuccess);

	if (linkingSuccess == GL_FALSE)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout << "SHADER_FILENAME:" << shaderName << std::endl;
		system("pause");
		exit(0);
	}
	programs[shaderName] = program;
}

const GLuint BasicEngine::Managers::ShaderManager::GetShader(const std::string &shaderName)
{
	return programs.at(shaderName);
}

std::string BasicEngine::Managers::ShaderManager::ReadShader(const std::string & filename)
{
	std::ifstream shaderFile;
	std::string shaderCode;
	shaderFile.exceptions(std::ifstream::badbit);

	try {
		shaderFile.open(filename);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n"
			<< "SHADER_FILENAME:" << filename.c_str() << std::endl;
	}
	
	return shaderCode ;
}

GLuint BasicEngine::Managers::ShaderManager::CreateShader(GLenum shaderType, const std::string & source, const std::string & shaderName)
{
	GLint success = 0;

	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderSource = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderSource, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		std::cout<< "SHADER_FILENAME:" << shaderName << std::endl;
		return 0;
	}
	
	return shader;
}


