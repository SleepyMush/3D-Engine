#include <iostream>
#include "Core/Windows.h"

Window windows;

extern "C" {
	__declspec(dllexport) uint32_t NvOptimusEnablement = 1;
}

int main() 
{
	windows.init();
	windows.run();

	return 0;
}


