#pragma once

class Window
{
public:
	Window(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);
	const HWND GetHWND() const { return _hwnd; }
	const bool IsQuit();
private:
	HWND _hwnd;
};