#include "Scene.h"
#include "../Render/Shader.h"

Shader shader;

struct Vertex
{
	glm::vec2 position;
};
unsigned int VBO, VAO;
std::vector<Vertex> vertices;

void Scene::loadScene()
{
	shader.load("res/shader/Main.vert", "res/shader/Main.frag");

	Vertex v0;
	Vertex v1;
	Vertex v2;
	Vertex v3;
	v0.position = glm::vec2(-0.5f, -0.5f);
	v1.position = glm::vec2(0.5f, -0.5f);
	v2.position = glm::vec2(0.5f, 0.5f);
	v3.position = glm::vec2(-0.5f, 0.5f);
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v3);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

}

void Scene::renderScene()
{
	shader.use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}
