#pragma once

#include <BasicEngine\Rendering\Models\Model.h>
#include "MazeGenerator.h"
#include <glm\gtx\transform.hpp>
#include <chrono>


using namespace BasicEngine::Rendering::Models;

typedef std::chrono::high_resolution_clock HiResTime;
typedef std::chrono::milliseconds MiliSec;
typedef std::chrono::duration<GLfloat> DeltaTime;

class MultiTextSphere : public Model {
public:
	MultiTextSphere();
	~MultiTextSphere();

	void CreateSphere(GLfloat radius, unsigned int rings, unsigned int sectors);
	virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;

};