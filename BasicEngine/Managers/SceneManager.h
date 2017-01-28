#pragma once

#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"
#include "../Core/Camera.h"
#include "../Input.h"
#include "..\..\Maze\MazeGenerator.h"

namespace BasicEngine {
	namespace Managers
	{
		class SceneManager : public Core::IListener
		{
		public:
			SceneManager();
			~SceneManager();

			virtual void NotifyBeginFrame();
			virtual void NotifyDisplayFrame();
			virtual void NotifyEndFrame();
			virtual void NotifyReshape(int width, int heightm, int previousWidth, int previousHeight);


			void SetModelsManager(Managers::ModelsManager*& modelsManager);


		private:
			Managers::ModelsManager* modelsManager;
			glm::mat4 projectionMatrix;
			glm::mat4 translationMatrix;
		};
	}
}