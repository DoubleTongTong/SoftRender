#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

#include "TWrapModeRenderTask.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    TBasicWindow win(hInstance);

    TWrapModeRenderTask task(TWrapMode::Mirror);
    win.SetRenderTask(&task);

    win.RunMessageLoop();
    return 0;
}