#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"

class TCubeRenderTask : public IRenderTask
{
    float m_angle;
    TPassThroughColorShader m_shader;

public:
    TCubeRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};