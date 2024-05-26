#pragma once
#include "IRenderTask.h"

class TColorfulTriangleRenderTask : public IRenderTask
{
public:
    virtual void Render(TSoftRenderer& sr) override;
};