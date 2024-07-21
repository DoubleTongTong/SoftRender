#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

#include "TImageTextureRenderTask.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    TBasicWindow win(hInstance);

    TImageTextureRenderTask task(win);
    win.SetRenderTask(&task);

    win.RunMessageLoop();
    return 0;
}