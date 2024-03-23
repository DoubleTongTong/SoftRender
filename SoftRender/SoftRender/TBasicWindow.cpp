#include "TBasicWindow.h"
#include <assert.h>

TBasicWindow::TBasicWindow(HINSTANCE hInst,
    int width, int height,
    LPCWSTR windowTitle,
    LPCWSTR className)
    : m_hInstance(hInst),
      m_className(className),
      m_pRenderTask(NULL)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = className;
    RegisterClassW(&wc);

    m_hWnd = Create(windowTitle, width, height);
    m_hDC = GetDC(m_hWnd);
}

TBasicWindow::~TBasicWindow()
{
    DeleteObject(m_hBitmap);
    DeleteDC(m_hMemDC);
    ReleaseDC(m_hWnd, m_hDC);

    UnregisterClassW(m_className, m_hInstance);
}

void TBasicWindow::RunMessageLoop()
{
    MSG msg = {};
    bool running = true;

    while (running)
    {
        /**
         * @brief 更新和渲染新的帧。
         */
        UpdateFrame();

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                continue;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

HWND TBasicWindow::Create(LPCWSTR windowTitle, int width, int height)
{
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;

	/**
     * @note 调整窗口尺寸以匹配客户区
     *
     * 这边 width 和 height 是客户区的大小。
     * 但是，窗口的总尺寸还包括边框、标题栏等其他部分。
     * 使用 AdjustWindowRect，我们可以根据客户区的期望尺寸来调整窗口的总尺寸，
     * 从而确保客户区的尺寸与我们预期的 width 和 height 相匹配。
     */
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hWnd = CreateWindowEx(0, m_className, windowTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, m_hInstance, NULL);

    if (hWnd == NULL)
    {
        return NULL;
    }

    ShowWindow(hWnd, SW_SHOW);

	/**
     * @brief 初始化绘图相关资源。
     *
     * 该函数完成以下操作：
     * 1. 创建一个内存设备上下文 (Memory DC)，用于离屏绘制。
     * 2. 根据指定的宽度和高度创建一个 DIBSection，这可以使我们直接访问图像数据。
     * 3. 将创建的 DIBSection 选入内存 DC，使得在该 DC 上的绘制都会反映到这个 DIBSection 上。
     * 4. 初始化光栅器，设置其绘图目标为 DIBSection 的数据，并清空为红色。
     */
	CreateDrawResources(width, height);
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

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// 不在这里使用 BitBlt，因为 WM_PAINT 消息处理可能导致绘制延迟。
        // 为了保证实时渲染，我们会直接在渲染函数中调用 BitBlt。
		//BitBlt(hdc, 0, 0, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, m_hMemDC, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

		EndPaint(hwnd, &ps);

		return 0;
	}
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void TBasicWindow::CreateDrawResources(int width, int height)
{
    m_hMemDC = CreateCompatibleDC(NULL); // 创建内存DC

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;  // top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    m_hBitmap = CreateDIBSection(m_hMemDC, &bmi, DIB_RGB_COLORS, &m_pBits, NULL, 0);

    assert(m_hBitmap != NULL && "Failed to create DIBSection!");

    SelectObject(m_hMemDC, m_hBitmap);

    m_rz = TRasterizer((uint32_t*)m_pBits, width, height);
    m_rz.Clear(TRGBA(255, 0, 0));
}

void TBasicWindow::UpdateFrame()
{
    ULONGLONG currentTime = GetTickCount64();
    ULONGLONG deltaTime = currentTime - m_lastRenderTime;

    if (deltaTime >= FRAME_DURATION)
    {
        // 执行渲染任务
        if (m_pRenderTask)
        {
            m_pRenderTask->Render(m_rz);

            BitBlt(m_hDC, 0, 0, m_rz.GetWidth(), m_rz.GetHeight(), m_hMemDC, 0, 0, SRCCOPY);
        }

        m_lastRenderTime = currentTime;
    }
}

void TBasicWindow::SetRenderTask(IRenderTask* renderTask)
{
    m_pRenderTask = renderTask;
}