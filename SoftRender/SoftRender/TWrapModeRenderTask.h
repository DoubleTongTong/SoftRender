#pragma once
#include "IRenderTask.h"

class TWrapModeRenderTask : public IRenderTask
{
    TImage m_texture;
    TWrapMode m_wrapMode;
public:
    TWrapModeRenderTask(TWrapMode mode);
    virtual void Render(TRasterizer& rz) override;
};