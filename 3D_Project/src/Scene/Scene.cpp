#include "Scene.h"
#include "../Core/Windows.h"
#include "../Render/Shader.h"
#include <GLFW/glfw3.h>

Shader shader;
Window window;

struct Vertex
{
	glm::vec3 position;
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
	Vertex v4;
	Vertex v5;
	Vertex v6;
	Vertex v7;

	v0.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v1.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v2.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v3.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v4.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v5.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v6.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v7.position = glm::vec3(-0.5f, 0.5f, 0.5f);

	//Front face
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v3);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	//Right face
	vertices.push_back(v1);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v6);
	vertices.push_back(v2);
	vertices.push_back(v1);

	//Back face
	vertices.push_back(v5);
	vertices.push_back(v4);
	vertices.push_back(v7);
	vertices.push_back(v7);
	vertices.push_back(v6);
	vertices.push_back(v5);

	//Left face
	vertices.push_back(v4);
	vertices.push_back(v0);
	vertices.push_back(v3);
	vertices.push_back(v3);
	vertices.push_back(v7);
	vertices.push_back(v4);

	//Top face
	vertices.push_back(v3);
	vertices.push_back(v2);
	vertices.push_back(v6);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v3);

	//Bottom face
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v1);
	vertices.push_back(v1);
	vertices.push_back(v0);
	vertices.push_back(v4);


	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

}

void Scene::renderScene()
{
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)window.screen_width / (float)window.screen_height, 0.1f, 100.0f);

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}
