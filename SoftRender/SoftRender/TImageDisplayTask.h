#pragma once

#include "IRenderTask.h"

class TImageDisplayTask : public IRenderTask
{
    TImage m_img, m_image_png;
public:
    TImageDisplayTask();
    virtual void Render(TSoftRenderer& sr) override;
};