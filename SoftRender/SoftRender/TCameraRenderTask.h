#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"
#include "TCameraController.h"

class TCameraRenderTask : public IRenderTask
{
    TPassThroughColorShader m_shader;
    TCameraController m_camera;

public:
    TCameraRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;
};