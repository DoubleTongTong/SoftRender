#include "TRandomDotRenderTask.h"
#include <stdlib.h>

void TRandomDotRenderTask::Render(TSoftRenderer& sr)
{
    for (int i = 0; i < sr.GetRenderWidth(); i++)
    {
        for (int j = 0; j < sr.GetRenderHeight(); j++)
        {
            uint8_t v = rand() % 255;
            sr.SetPixel(i, j, TRGBA(v, v, v));
        }
    }
}