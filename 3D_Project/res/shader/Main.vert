#version 460 core
layout (location = 0) in vec2 position;

out vec4 vertexColor; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}