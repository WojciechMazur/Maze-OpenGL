#pragma once

#include <map>
#include "ShaderManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"


using namespace BasicEngine::Rendering;
namespace BasicEngine {
	namespace Managers
	{
		class ModelsManager
		{
		public:
			ModelsManager();
			~ModelsManager();

			void Draw();
			void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
			void Update();

			void DeleteModel(const std::string& gameModelName);
			const IGameObject& GetModel(const std::string& gameModelName) const;

			void DeleteModel_NDC(const std::string& gameModelName);
			const IGameObject& GetModel_NDC(const std::string& gameModelName) const;
			void SetModel(const std::string& gameObjectName, IGameObject* gameObject);

		private:
			std::map<std::string, IGameObject*> gameModelList;
			std::map<std::string, IGameObject*> gameModelList_NDC;
		};
	}
}