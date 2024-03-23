#include "TRandomDotRenderTask.h"
#include <stdlib.h>

void TRandomDotRenderTask::Render(TRasterizer& rz)
{
    for (int i = 0; i < rz.GetWidth(); i++)
    {
        for (int j = 0; j < rz.GetHeight(); j++)
        {
            uint8_t v = rand() % 255;
            rz.SetPixel(i, j, TRGBA(v, v, v));
        }
    }
}