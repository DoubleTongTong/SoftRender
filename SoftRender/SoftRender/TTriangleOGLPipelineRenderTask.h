#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"

class TTriangleOGLPipelineRenderTask : public IRenderTask
{
public:
    TTriangleOGLPipelineRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;
};