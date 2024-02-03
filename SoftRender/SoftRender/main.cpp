#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

#include "TColorfulTriangleRenderTask.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    TBasicWindow win(hInstance);

    TColorfulTriangleRenderTask task;
    win.SetRenderTask(&task);

    win.RunMessageLoop();
    return 0;
}