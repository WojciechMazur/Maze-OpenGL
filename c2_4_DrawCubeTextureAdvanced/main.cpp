#pragma once

#include <BasicEngine\Core\Engine.h>
#include "CubeTexturedAdvanced.h"
#include <SOIL2\SOIL2.h>

using namespace BasicEngine;


int main(int argc, char **argv)
{
	std::cout << "Advanded textured cube\n";
	Engine* engine = new Engine();
	engine->Init();

	Camera* activeCamera = new Camera();

	engine->getShaderManager()->CreateProgram("CubeTexShader", 
		"Shaders\\CubeTexVertexShader.glsl",
		"Shaders\\CubeTexFragmentShader.glsl");

	CubeTexturedAdvanced* cube= new CubeTexturedAdvanced();
	
	int program = engine->getShaderManager()->GetShader("CubeTexShader");
	if (program != 0)
	{
		cube->SetProgram(program);
		cube->Create();
	}
	else
	{
		std::cout << "Invalid program...";
		std::cin.get();
	}
	
	cube->SetTexture("Crate", SOIL_load_OGL_texture("Textures\\Crate.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

		
	engine->getModelsManager()->SetModel("cube", cube);

	engine->Run();

	delete engine;

	return 0;
}