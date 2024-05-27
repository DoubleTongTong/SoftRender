#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"

class TTriangleOGLPipelineRenderTask : public IRenderTask
{
    TSimpleShader m_shader;
    float m_angle;

public:
    TTriangleOGLPipelineRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};