#pragma once

#include <Windows.h>
#include "TRasterizer.h"
#include "IRenderTask.h"

class TBasicWindow
{
public:
	TBasicWindow(HINSTANCE hInst,
		int width = 800, int height = 600,
		LPCWSTR windowTitle = L"DefaultWindowTitle",
		LPCWSTR className = L"DefaultTBasicWindowClass");
	~TBasicWindow();
	void RunMessageLoop();
	void SetRenderTask(IRenderTask* renderTask);
private:
	HWND Create(LPCWSTR windowTitle, int width, int height);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;
	HWND      m_hWnd;
	LPCWSTR   m_className;

	HDC     m_hDC; // �豸������
	HDC     m_hMemDC;
	HBITMAP m_hBitmap;
	void*   m_pBits;    // ָ��DIBSection���ݵ�ָ��

	TRasterizer  m_rz;
	IRenderTask* m_pRenderTask;

	DWORD m_lastRenderTime;
	const int TARGET_FPS = 30;
	const int FRAME_DURATION = 1000 / TARGET_FPS; // in milliseconds
public:
	TBasicWindow(const TBasicWindow&) = delete;
	TBasicWindow& operator=(const TBasicWindow&) = delete;
	TBasicWindow(TBasicWindow&&) = delete;
	TBasicWindow& operator=(TBasicWindow&&) = delete;

private:
	void CreateDrawResources(int width, int height);
	void UpdateFrame();
};
