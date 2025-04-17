#include "Window.h"

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName)
{
	_width = clientWidth;
	_height = clientHeight;

	WNDCLASSEX wndClass = {};

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WindowProcedure;
	wndClass.lpszClassName = windowClassName.c_str();
	wndClass.hInstance = GetModuleHandle(nullptr);

	if (!RegisterClassEx(&wndClass))
	{
		assert(false && "RegisterClassEx failed");
	}

	_hwnd = CreateWindow(
		windowClassName.c_str(),
		titleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		clientWidth,
		clientHeight,
		nullptr,
		nullptr,
		wndClass.hInstance,
		this
	);

	if (_hwnd == nullptr)
	{
		assert(false && "CreateWindow is failed");
	}

	ShowWindow(_hwnd, SW_SHOW);

	UpdateWindow(_hwnd);
}


const bool Window::IsQuit()
{
	MSG msg = {};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.message == WM_QUIT);
}