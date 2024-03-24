#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

#include "TImageDisplayTask.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    TBasicWindow win(hInstance);

    TImageDisplayTask task;
    win.SetRenderTask(&task);

    win.RunMessageLoop();
    return 0;
}