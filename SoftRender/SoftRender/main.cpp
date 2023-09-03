#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

class CustomRenderTask : public IRenderTask
{
public:
    virtual void Render(TRasterizer& rz) override
    {
        for (int i = 0; i < rz.GetWidth(); i++)
        {
            for (int j = 0; j < rz.GetHeight(); j++)
            {
                uint8_t v = rand() % 255;
                rz.SetPixel(i, j, TRasterizer::MakeRGB(v, v, v));
            }
        }
    }
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    TBasicWindow win(hInstance);

    CustomRenderTask task;
    win.SetRenderTask(&task);

    win.RunMessageLoop();
    return 0;
}