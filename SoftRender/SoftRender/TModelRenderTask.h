#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TLambertianShader.h"
#include "TCameraController.h"
#include "TModel.h"

class TModelRenderTask : public IRenderTask
{
    TLambertianShader m_shader;
    TCameraController m_camera;
    TModel m_model;

    float m_angle;
public:
    TModelRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;
};