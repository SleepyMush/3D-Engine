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
unsigned int GVBO, GVAO, IBO;
std::vector<Vertex> vertices;

std::vector<glm::vec3> vertex;
std::vector<glm::uvec4> index;

int slice = 10;
unsigned int lenght = 0;
float Scale = 10.0f;

void Scene::loadScene()
{
	//Loads Cube
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


	//Loads Grid

	//Vertex
	for (int v = 0; v <= slice; ++v){
		for (int i = 0; i <= slice; ++i) {
			float x = (float)i / (float)slice;
			float y = 0;
			float z = (float)v / (float)slice;

			glm::vec3 scaledVertex = glm::vec3(x, y, z) * Scale;
			vertex.push_back(scaledVertex);
		}
	}

	//Index
	for (int v = 0; v < slice; ++v) {
		for (int i = 0; i < slice; ++i) {
			int row1 = v * (slice + 1);
			int row2 = (v+1) * (slice + 1);
			index.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
			index.push_back(glm::uvec4(row2 + i + 1, row2 + i , row2 + i , row1 + i));
		}
	}


	glGenBuffers(1, &GVBO);
	glGenVertexArrays(1, &GVAO);
	glBindVertexArray(GVAO);

	glBindBuffer(GL_ARRAY_BUFFER, GVBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), vertex.data(), GL_STATIC_DRAW);

	//// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(index.data()), index.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	lenght = (GLuint)index.size() * 4;
}

void Scene::renderScene()
{
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	float x, y, z;
	x = 5;
	y = 0;
	z = 1;
	model = glm::translate(model, glm::vec3(x, y, z));

	glm::vec3 _cameraPos(0.0f);
	glm::mat4 cameraMat(1.0f);
	cameraMat = glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * cameraMat;
	cameraMat = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * cameraMat;
	cameraMat = glm::translate(cameraMat, glm::vec3(0.0f, 0.0f, 5.0f));
	view = glm::inverse(cameraMat);
	view = glm::translate(view, _cameraPos);

	projection = glm::perspective(glm::radians(45.0f), (float)window.screen_width / (float)window.screen_height, 0.1f, 100.0f);

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);

	//Grid
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", glm::mat4(1.0f));
	glBindVertexArray(GVAO);
	glDrawElements(GL_LINES, lenght, GL_UNSIGNED_INT, NULL);

}
