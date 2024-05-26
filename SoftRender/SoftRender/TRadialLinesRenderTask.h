#pragma once
#include "IRenderTask.h"

class TRadialLinesRenderTask : public IRenderTask
{
public:
    virtual void Render(TSoftRenderer& sr) override;
};