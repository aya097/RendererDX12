#include "Window/Window.h"
#include "Renderer/GraphicsDevice.h"
#include "Scene/Scene.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Debugの起動
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// ComPtrの初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// ウィンドウの初期化
	constexpr int width = 1280;
	constexpr int height = 720;
	Window window(width, height, L"AAA", L"WINDOW");

	// グラフィックスエンジンの初期化
	g_GraphicsDevice = new GraphicsDevice(window.GetHWND(), width, height);

	// シーンの初期化
	g_Scene = new Scene();
	g_Scene->Init();

	while (!window.IsQuit())
	{
		g_Scene->Update();
		g_GraphicsDevice->BeginRender();
		g_Scene->Draw();
		g_GraphicsDevice->EndRender();
	}

	return 0;
}