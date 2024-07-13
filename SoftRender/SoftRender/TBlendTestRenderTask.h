#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"

class TBlendTestRenderTask : public IRenderTask
{
    TPassThroughColorShader m_shader;

public:
    TBlendTestRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;
};