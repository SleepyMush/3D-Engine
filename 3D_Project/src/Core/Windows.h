#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Window {
private:
	GLFWwindow* window;
public:
	int screen_width = 1920;
	int screen_height = 1080;
	Window(): window(nullptr) {};

	void init();
	void run();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};



