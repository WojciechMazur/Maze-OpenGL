#ifndef VertexFormat_H_
#define VertexFormat_H_

#include "glm\glm.hpp"
namespace BasicEngine {
	namespace Rendering {

		struct VertexFormat
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 texture;

			VertexFormat(const glm::vec3 &_position, const glm::vec4 &_color) :
				position(_position),
				color(_color)
			{
				texture.x = texture.y = 0;
			};

			VertexFormat(const glm::vec3 &_position, const glm::vec2 &_texture)
			{
				position = _position;
				texture = _texture;
				color.r = color.g = color.b = color.a = 0;
			}

			VertexFormat(){}

		};
	}
}
#endif // !
