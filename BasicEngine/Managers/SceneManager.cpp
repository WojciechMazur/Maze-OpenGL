#include "SceneManager.h"

using namespace BasicEngine::Managers;

extern BasicEngine::Camera* activeCamera;

SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);
	
	translationMatrix = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);
}

SceneManager::~SceneManager() {

}


void SceneManager::NotifyBeginFrame() {
	
	modelsManager->Update();
}

void SceneManager::NotifyDisplayFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	modelsManager->Draw();
	modelsManager->Draw(projectionMatrix, translationMatrix);

	if (glm::length(activeCamera->getPosition() -
		glm::vec3(Maze::MazeGenerator::finishPosition->x * 2, 0, Maze::MazeGenerator::finishPosition->y * 2)) < 1)
		glutLeaveMainLoop();
}

void SceneManager::NotifyEndFrame() {

	
}

void SceneManager::NotifyReshape(int width, int height, int previousWidth, int previousHeight) {
	
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projectionMatrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	projectionMatrix[2][2] = (-near1 - far1) / (near1 - far1);
	projectionMatrix[2][3] = 1.0f;
	projectionMatrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}


void BasicEngine::Managers::SceneManager::SetModelsManager(Managers::ModelsManager* & _modelsManager)
{
	modelsManager = _modelsManager;
}

