#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include <iostream>
#include <GL\freeglut.h>
using namespace BasicEngine;



Camera::Camera() :
	viewDirection(0.0f, 0.0f, -1.0f),
	position(0.0f, 0.0f, 0.0f),
	UP(0.0f, 1.0f, 0.0f) {};

BasicEngine::Camera::Camera(const glm::vec3 & _position, const glm::vec3 & _viewDirection) : UP(0.0f, 1.0f, 0.0f)
{
	position = _position;
	viewDirection = _viewDirection;
}


glm::mat4 Camera::getWorldToViewMatrix()
{
	if(BasicEngine::Input::freeCamMode==false)
		this->computePhysic();
	
	return glm::lookAt(position, position + viewDirection, UP);
}

void BasicEngine::Camera::specialKeysInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		moveForward();
		break;
	case GLUT_KEY_DOWN:
		moveBackward();
		break;
	case GLUT_KEY_LEFT:
		strafeLeft();
		break;
	case GLUT_KEY_RIGHT:
		strafeRight();
		break;
	case GLUT_KEY_END:
		glutLeaveMainLoop();
		break;
	case GLUT_KEY_F1:
			glutFullScreen();
			break;
	case GLUT_KEY_F2:
		glutLeaveFullScreen();
		break;
	case GLUT_KEY_F3:
		if (BasicEngine::Input::freeCamMode==true)
			BasicEngine::Input::freeCamMode = false;
		else
			BasicEngine::Input::freeCamMode = true;
		break;
	default:
		glutPostRedisplay();
	}
}

void BasicEngine::Camera::normalKeysInput(unsigned int key, int x, int y)
{
	switch (key)
	{
	case 'w':
		moveForward();
		break;
	case 's':
		moveBackward();
		break;
	case 'a':
		strafeLeft();
		break;
	case 'd':
		strafeRight();
		break;
	default:
		break;
	}
}

void BasicEngine::Camera::setPosition(float xx, float yy, float zz)
{
	position.x = xx;
	position.y = yy;
	position.z = zz;
}

glm::vec3 BasicEngine::Camera::getPosition()
{
	return position;
}

void BasicEngine::Camera::computePhysic()
{
	//std::cout << "Pre compute physic" << position.x << "," << position.y << "," << position.z << std::endl;
	if (this->position.y > 0.01f)
		position.y = position.y - BasicEngine::Input::gravityForce * exp(position.y);
	else
	if (this->position.y < -0.01f)
		position.y = position.y + BasicEngine::Input::gravityForce* exp(-position.y);
	//std::cout << "After compute physic" << position.x << "," << position.y << "," << position.z << std::endl << std::endl;


}

void Camera::mouseUpdate(int x, int y)
{
	glm::vec2 newMousePosition(x, y);
	glm::vec2 mouseDelta = (newMousePosition - BasicEngine::Input::mousePostion);
	if (glm::length(mouseDelta) < 39.0f)
	{
		strafeDirection = glm::cross(viewDirection, UP);
		glm::mat4 rotator = glm::rotate(mouseDelta.x * BasicEngine::Input::sensitivityX, UP) *
							glm::rotate(mouseDelta.y * BasicEngine::Input::sensitivityY, strafeDirection);

		viewDirection = glm::mat3(rotator) * viewDirection;
	}
	BasicEngine::Input::mousePostion = newMousePosition;
}
							 
void Camera::moveForward() {
	position += -BasicEngine::Input::movementSpeed * viewDirection;
}
void Camera::moveBackward() {
	position += BasicEngine::Input::movementSpeed * viewDirection;
}

void Camera::strafeLeft(){
	position += -strafeDirection * BasicEngine::Input::movementSpeed;
}
void Camera::strafeRight() {
	position += strafeDirection * BasicEngine::Input::movementSpeed;
}

bool BasicEngine::Camera::checkForCollision(glm::vec3 newPosition, Array2D<Maze::EObject>* levelMap) const
{
	if(*levelMap->operator()(newPosition.x, newPosition.z)==Maze::EObject::SPACE)
		return false;
	return true;
}

