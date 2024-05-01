#include <iostream>
#include "Core/Windows.h"
#include "Render/Shader.h"

Window windows;
Shader Myshader;

int main() 
{
	windows.init();
	windows.run();
	Myshader.load("res/shader","res/shad");
	Myshader.use();

	return 0;
}


