#pragma once

#include "..\BasicEngine\Rendering\Models\Model.h"
#include <time.h>
#include <stdarg.h>
#include "..\BasicEngine\Input.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

using namespace BasicEngine::Rendering::Models;

class CubeTexturedAdvanced : public Model
{
public:
	CubeTexturedAdvanced();
	~CubeTexturedAdvanced();

	void Create();
	virtual void Draw(const glm::mat4& projectionMatrix,
		const glm::mat4& translationMatrix)
		override final;
	virtual void Update() override final;

private:
	glm::vec3 rotation, rotationSpeed;
	glm::vec3 rotationSin;
	time_t timer;
};
