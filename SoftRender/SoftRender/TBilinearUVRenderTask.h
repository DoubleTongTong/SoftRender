#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"

class TBilinearUVRenderTask : public IRenderTask
{
    TImage m_texture;

    tmath::Point2i p1, p2, p3, p4;
    tmath::UV2f uv1, uv2, uv3, uv4;
public:
    TBilinearUVRenderTask(TBasicWindow& win);
    virtual void Render(TRasterizer& rz) override;
};