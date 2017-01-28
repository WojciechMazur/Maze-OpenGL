#pragma once

#include <BasicEngine\Core\Engine.h>
#include "CubeTexturedInstanced.h"
#include "MultiTextSphere.h"
#include <SOIL2\SOIL2.h>
#include "MazeGenerator.h"
#include <glm\glm.hpp>

using namespace BasicEngine;


int main(int argc, char **argv)
{
	size_t initSizeX, initSizeY;
	std::cout << "Insert maze size: X, Y: ";
	std::cin >> initSizeX >> initSizeY;

	Maze::MazeGenerator level01(initSizeX, initSizeY);
	level01.generate();
	level01.print();
	
	Engine* engine = new Engine();
	engine->Init();

	engine->getShaderManager()->CreateProgram("CubeTexShader",
		"Shaders\\CubeTexVertexShader.glsl",
		"Shaders\\CubeTexFragmentShader.glsl");

	engine->getShaderManager()->CreateProgram("MultiTextSphereShader",
		"Shaders\\VertexShader.glsl",
		"Shaders\\FragmentShader.glsl");

	CubeTexturedInstanced* cube = new CubeTexturedInstanced(&level01);
	MultiTextSphere* sphere = new MultiTextSphere();

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

	program = engine->getShaderManager()->GetShader("MultiTextSphereShader");
	if (program != 0)
	{
		sphere->SetProgram(program);
		sphere->CreateSphere(1, 256, 256);
	}
	else
	{
		std::cout << "Invalid program...";
		std::cin.get();
	}

	sphere->SetTexture("BaseTexture", SOIL_load_OGL_texture("Textures\\nebula1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	sphere->SetTexture("SecondTexture", SOIL_load_OGL_texture("Textures\\nebula2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	sphere->SetTexture("ThirdTexture", SOIL_load_OGL_texture("Textures\\nebula3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	sphere->SetTexture("AlphaChanTexture", SOIL_load_OGL_texture("Textures\\alphaChan.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));
	sphere->SetTexture("RampTexture", SOIL_load_OGL_texture("Textures\\ramp.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS));


	engine->getModelsManager()->SetModel("sphere", sphere);

	engine->Run();
	delete engine;

	return 0;
}

