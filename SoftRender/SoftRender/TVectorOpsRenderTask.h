#pragma once
#include "IRenderTask.h"

class TVectorOpsRenderTask : public IRenderTask
{
public:
    virtual void Render(TSoftRenderer& sr) override;
};