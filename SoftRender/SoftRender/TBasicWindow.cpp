#include "TBasicWindow.h"

TBasicWindow::TBasicWindow(HINSTANCE hInst,
    int width, int height,
    LPCWSTR windowTitle,
    LPCWSTR className)
    : m_hInstance(hInst),
    m_className(className)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = className;
    RegisterClassW(&wc);

    m_hWnd = Create(windowTitle, width, height);

}

TBasicWindow::~TBasicWindow()
{
    UnregisterClassW(m_className, m_hInstance);
}

void TBasicWindow::RunMessageLoop() {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND TBasicWindow::Create(LPCWSTR windowTitle, int width, int height)
{
    HWND hWnd = CreateWindowEx(0, m_className, windowTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        width, height, NULL, NULL, m_hInstance, NULL);

    if (hWnd == NULL)
    {
        return NULL;
    }

    ShowWindow(hWnd, SW_SHOW);

    return hWnd;
}

LRESULT CALLBACK TBasicWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

