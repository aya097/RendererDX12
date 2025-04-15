#pragma once
#include <Windows.h>
#include <string>
#include <assert.h>

class Window
{
public:
	Window(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);
	const HWND GetHWND() const { return _hwnd; }

	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);

	const bool IsQuit();
private:
	HWND _hwnd;
};