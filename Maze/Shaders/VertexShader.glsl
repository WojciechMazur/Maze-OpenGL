#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;

uniform mat4 projectionMatrix, viewMatrix, camera;
uniform vec3 rotation;

out vec2 texcoord;

void main()
{
	texcoord = in_texture;
	gl_Position = projectionMatrix * camera * viewMatrix * vec4(in_position, 1);
	
}