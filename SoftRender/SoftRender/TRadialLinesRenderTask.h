#pragma once
#include "IRenderTask.h"

class TRadialLinesRenderTask : public IRenderTask
{
public:
    virtual void Render(TRasterizer& rz) override;
};