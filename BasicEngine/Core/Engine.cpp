#include "Engine.h"

using namespace BasicEngine;
using namespace Core;


Engine::Engine()
{
}

bool Engine::Init() {
	WindowInfo window(std::string("Maze 0.1"), 0,0, 1920,1080, true);
	ContextInfo context(4, 3, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init::GLUT::init(window, context, frameBufferInfo);

	mSceneManager = new Managers::SceneManager();

	Init::GLUT::setListener(mSceneManager);

	mShaderManager = new Managers::ShaderManager();
	mShaderManager->CreateProgram("BasicShader",
		"..\\BasicEngine\\Shaders\\BasicVertexShader.glsl",
		"..\\BasicEngine\\Shaders\\BasicFragmentShader.glsl");

	mTextureLoader = new TextureLoader();

	if (mSceneManager && mShaderManager)
	{
		mModelsManager = new Managers::ModelsManager();
		mSceneManager->SetModelsManager(mModelsManager);
	}
	else
		return false;
	return true;
}

void Engine::Run()
{
	Init::GLUT::run();
}

Managers::SceneManager* Engine::getSceneManager() const
{
	return mSceneManager;
}

Managers::ModelsManager* Engine::getModelsManager() const
{
	return mModelsManager;
}


Managers::ShaderManager* Engine::getShaderManager() const
{
	return mShaderManager;
}

TextureLoader* Engine::GetTextureLoader() const {
	return mTextureLoader;
}


Engine::~Engine()
{
	if (mSceneManager)
		delete mSceneManager;
	if (mShaderManager)
		delete mShaderManager;
	if (mModelsManager)
		delete mModelsManager;
	if (mTextureLoader)
		delete mTextureLoader;
}

