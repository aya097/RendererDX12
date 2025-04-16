#pragma once

class Window
{
public:
	Window(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);
	const HWND GetHWND() const { return _hwnd; }
	constexpr int GetWidth() const { return _width; }
	constexpr int GetHeight() const { return _height; }
	const bool IsQuit();
private:
	HWND _hwnd;
	int _width;
	int _height;
};