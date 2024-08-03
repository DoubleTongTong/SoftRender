#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TLambertianShader.h"
#include "TCameraController.h"

class TLambertianRenderTask : public IRenderTask
{
    TLambertianShader m_shader;
    TCameraController m_camera;

public:
    TLambertianRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;
};