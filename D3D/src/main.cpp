#include "Window.h"
#include <Windows.h>

using namespace d3d;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	Window window(640, 480, "D3D", hInstance);

	return EXIT_SUCCESS;
}