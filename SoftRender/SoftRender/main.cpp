#include "TBasicWindow.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

#include <algorithm>
class CustomRenderTask : public IRenderTask
{
public:
    virtual void Render(TRasterizer& rz) override
    {
        int centerX = rz.GetWidth() / 2;
        int centerY = rz.GetHeight() / 2;

        const int angleInterval = 5;
        int r = std::min(rz.GetWidth(), rz.GetHeight()) / 2;

        rz.Clear(TRGB888(0, 0, 0));
        for (int angle = 0; angle < 360; angle += angleInterval)
        {
            float radian = angle * 3.14159265358979323846 / 180.0;
            
            int endX = centerX + cos(radian) * r;
            int endY = centerY + sin(radian) * r;

            rz.DrawLine(centerX, centerY, TRGB888(rand() % 255, rand() % 255, rand() % 255),
                        endX,    endY,    TRGB888(rand() % 255, rand() % 255, rand() % 255));
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