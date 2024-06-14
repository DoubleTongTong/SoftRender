#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"

class TTriangleOGLPipelineRenderTask : public IRenderTask
{
    TPassThroughColorShader m_shader;
    float m_angle;

public:
    TTriangleOGLPipelineRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};