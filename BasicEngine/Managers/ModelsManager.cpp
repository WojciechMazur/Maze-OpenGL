#include "ModelsManager.h"
using namespace BasicEngine;
using namespace Managers;
using namespace Rendering;


ModelsManager::ModelsManager()
{
	//To delete after end of tutorial

	/*Models::Triangle* triangle = new Models::Triangle();
	triangle->SetProgram(ShaderManager::GetShader("BasicShader"));
	triangle->Create();
	gameModelList_NDC["triangle"] = triangle;

	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("BasicShader"));
	quad->Create();
	gameModelList_NDC["quad"] = quad;*/
}



ModelsManager::~ModelsManager()
{
	for (auto model : gameModelList)
		delete model.second;
	gameModelList.clear();

	for (auto model : gameModelList_NDC)
		delete model.second;
	gameModelList_NDC.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

void ModelsManager::DeleteModel_NDC(const std::string& gameModelName)
{
	IGameObject* model = gameModelList_NDC[gameModelName];
	model->Destroy();
	gameModelList_NDC.erase(gameModelName);
}



const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

const IGameObject& ModelsManager::GetModel_NDC(const std::string& gameModelName) const
{
	return (*gameModelList_NDC.at(gameModelName));
}

void ModelsManager::SetModel(const std::string & gameObjectName, IGameObject * gameObject)
{
	gameModelList[gameObjectName.c_str()] = gameObject;
}

void ModelsManager::Update()
{
	
	for (auto model : gameModelList)
		model.second->Update();
	for (auto model : gameModelList_NDC)
		model.second->Update();
}

void ModelsManager::Draw()
{
	for (auto model : gameModelList_NDC)
		model.second->Draw();
}

void ModelsManager::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	for (auto model : gameModelList)
		model.second->Draw(projectionMatrix, viewMatrix);
}




