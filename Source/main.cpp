#include "Window/Window.h"
#include "Renderer/GraphicsDevice.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	constexpr int width = 1280;
	constexpr int height = 720;
	Window window(width, height, L"AAA", L"WINDOW");

	g_GraphicsDevice = new GraphicsDevice(window.GetHWND(), width, height);

	while (!window.IsQuit())
	{
		g_GraphicsDevice->BeginRender();
		g_GraphicsDevice->EndRender();
	}

	return 0;
}