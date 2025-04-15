#include "Window/Window.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	constexpr int width = 1280;
	constexpr int height = 720;
	Window window(width, height, L"AAA", L"WINDOW");

	while (!window.IsQuit())
	{

	}

	return 0;
}