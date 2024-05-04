#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

#include "TViewTransformRenderTask.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    TBasicWindow win(hInstance);

    TViewTransformRenderTask task(win);
    win.SetRenderTask(&task);

    win.RunMessageLoop();
    return 0;
}