#pragma once
#include <glm\glm.hpp>
#include "..\Input.h"
#include "..\..\Maze\MazeGenerator.h"
#include "..\..\Maze\Array2D.h"

namespace BasicEngine
{
	class Camera
	{
	private:
		glm::vec3 position;
		glm::vec3 viewDirection;
		glm::vec3 strafeDirection;
		const glm::vec3 UP;
	public:
		Camera();
		Camera(const glm::vec3& _position, const glm::vec3& _viewDirection);
		void mouseMove(int x, int y, int width, int height);
		void mouseUpdate(int x, int y);
		glm::mat4 getWorldToViewMatrix();
		void specialKeysInput(int key, int x, int y);
		void normalKeysInput(unsigned int key, int x, int y);
		void setPosition(float x, float y, float z);
		glm::vec3 getPosition();
		void computePhysic();

	private:
		void moveForward();
		void moveBackward();
		void strafeLeft();
		void strafeRight();
		bool checkForCollision(glm::vec3 newPosition, Array2D<Maze::EObject>* levelMap) const;
	};
}