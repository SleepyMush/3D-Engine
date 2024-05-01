#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window {
private:
	int screen_width = 1920;
	int screen_height = 1080;
	GLFWwindow* window;

public:
	Window(): window(nullptr) {};

	void init();
	void run();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};



