#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"

class TBackFaceCullingRenderTask : public IRenderTask
{
    TPassThroughColorShader m_shader;
    float m_angle;

public:
    TBackFaceCullingRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};