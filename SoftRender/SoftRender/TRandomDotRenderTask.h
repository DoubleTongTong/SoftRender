#pragma once
#include "IRenderTask.h"

class TRandomDotRenderTask : public IRenderTask
{
public:
    virtual void Render(TRasterizer& rz) override;
};