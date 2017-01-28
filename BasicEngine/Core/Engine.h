#pragma once
#include "../Core/Init/GLUT.h"
#include "../Managers/SceneManager.h"

namespace BasicEngine {
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Init();

		void Run();

		Managers::SceneManager* getSceneManager() const;
		Managers::ShaderManager* getShaderManager() const;
		Managers::ModelsManager* getModelsManager() const;
		TextureLoader* GetTextureLoader() const;
		

	private:
		Managers::SceneManager* mSceneManager;
		Managers::ShaderManager* mShaderManager;
		Managers::ModelsManager* mModelsManager;
		TextureLoader* mTextureLoader;
	public: 
		static Camera* activeCamera;

	};
}

