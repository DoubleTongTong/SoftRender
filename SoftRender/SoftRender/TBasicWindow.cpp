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
         * @brief ���º���Ⱦ�µ�֡��
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
     * @note �������ڳߴ���ƥ��ͻ���
     *
     * ��� width �� height �ǿͻ����Ĵ�С��
     * ���ǣ����ڵ��ܳߴ绹�����߿򡢱��������������֡�
     * ʹ�� AdjustWindowRect�����ǿ��Ը��ݿͻ����������ߴ����������ڵ��ܳߴ磬
     * �Ӷ�ȷ���ͻ����ĳߴ�������Ԥ�ڵ� width �� height ��ƥ�䡣
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
     * @brief ��ʼ����ͼ�����Դ��
     *
     * �ú���������²�����
     * 1. ����һ���ڴ��豸������ (Memory DC)�������������ơ�
     * 2. ����ָ���Ŀ�Ⱥ͸߶ȴ���һ�� DIBSection�������ʹ����ֱ�ӷ���ͼ�����ݡ�
     * 3. �������� DIBSection ѡ���ڴ� DC��ʹ���ڸ� DC �ϵĻ��ƶ��ᷴӳ����� DIBSection �ϡ�
     * 4. ��ʼ����դ�����������ͼĿ��Ϊ DIBSection �����ݣ������Ϊ��ɫ��
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

		// ��������ʹ�� BitBlt����Ϊ WM_PAINT ��Ϣ������ܵ��»����ӳ١�
        // Ϊ�˱�֤ʵʱ��Ⱦ�����ǻ�ֱ������Ⱦ�����е��� BitBlt��
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
    m_hMemDC = CreateCompatibleDC(NULL); // �����ڴ�DC

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

    m_windowWidth = width;
    m_windowHeight = height;

    m_sr.SetRasterizer((uint32_t*)m_pBits, width, height);
    m_sr.Clear(TRGBA(255, 0, 0));
}

void TBasicWindow::UpdateFrame()
{
#if 0
    ULONGLONG currentTime = GetTickCount64();
    ULONGLONG deltaTime = currentTime - m_lastRenderTime;

    if (deltaTime >= FRAME_DURATION)
    {
#endif
        // ִ����Ⱦ����
        if (m_pRenderTask)
        {
            m_pRenderTask->Render(m_sr);

            BitBlt(m_hDC, 0, 0, m_windowWidth, m_windowHeight, m_hMemDC, 0, 0, SRCCOPY);
        }
#if 0
        m_lastRenderTime = currentTime;
    }
#endif
}

void TBasicWindow::SetRenderTask(IRenderTask* renderTask)
{
    m_pRenderTask = renderTask;
}

int TBasicWindow::GetWindowWidth()
{
    return m_windowWidth;
}

int TBasicWindow::GetWindowHeight()
{
    return m_windowHeight;
}