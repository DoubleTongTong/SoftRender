#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"

class TDepthTestRenderTask : public IRenderTask
{
    TPassThroughColorShader m_shader;

public:
    TDepthTestRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;
};