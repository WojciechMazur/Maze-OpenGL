#pragma once
#include <glm\glm.hpp>
#include "Core\Camera.h"


namespace BasicEngine {
	namespace Input
	{
		static glm::vec2 mousePostion;
		static float sensitivityX = (float)0.01f;
		static float sensitivityY =  (float)0.01f;
		static float movementSpeed = (float)0.1f;
		static float gravityForce = (float)0.01f;
		static glm::vec3 cameraPosition(0, 0, 0);
		static bool freeCamMode = false;
	};
};

