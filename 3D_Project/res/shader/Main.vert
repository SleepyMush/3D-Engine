#version 460 core
layout (location = 0) in vec3 position;

out vec4 vertexColor; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
}


//void main()
//{
//	vec3 originalPos = position;
//	float offsetX = 5.0;
//	float offsetZ = 5.0;
//
//	vec3 adjustedPos = vec3(originalPos.x + offsetX, originalPos.y, originalPos.z + offsetZ);
//
//	gl_Position = projection * view * model * vec4(adjustedPos, 1.0);
//	vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
//}