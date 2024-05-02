#pragma once
#include "IRenderTask.h"

class TMatrixOpsTask : public IRenderTask
{
public:
    TMatrixOpsTask();
    virtual void Render(TRasterizer& rz) override;
};