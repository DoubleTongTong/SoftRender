#pragma once

#include <Windows.h>

class TBasicWindow
{
public:
	TBasicWindow(HINSTANCE hInst,
		int width = 800, int height = 600,
		LPCWSTR windowTitle = L"DefaultWindowTitle",
		LPCWSTR className = L"DefaultTBasicWindowClass");
	~TBasicWindow();
	void RunMessageLoop();

private:
	HWND Create(LPCWSTR windowTitle, int width, int height);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HWND      m_hWnd;
	LPCWSTR   m_className;

public:
	TBasicWindow(const TBasicWindow&) = delete;
	TBasicWindow& operator=(const TBasicWindow&) = delete;
	TBasicWindow(TBasicWindow&&) = delete;
	TBasicWindow& operator=(TBasicWindow&&) = delete;
};
