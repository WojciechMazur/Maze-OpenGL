#include "GLEW.h"


using namespace BasicEngine::Core;
using namespace BasicEngine::Core::Init;

void GLEW::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
		std::cout << "GLEW: Initialize" << std::endl; 
	int s = glGetError();
	if (glewIsSupported("GL_VERSION_4_3"))
		std::cout << "GLEW GL_VERSION_4_3 is 4.3\n ";
	else
		std::cout << "GLEW GL_VERSION_4_3 not supported\n";
}