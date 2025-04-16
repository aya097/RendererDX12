#include "Window/Window.h"
#include "Renderer/GraphicsDevice.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	constexpr int width = 1280;
	constexpr int height = 720;
	Window window(width, height, L"AAA", L"WINDOW");

	g_GraphicsDevice = new GraphicsDevice(window.GetHWND(), width, height);

	while (!window.IsQuit())
	{

	}

	return 0;
}