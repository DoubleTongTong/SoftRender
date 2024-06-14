#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughColorShader.h"

class TClippingRenderTask : public IRenderTask
{
    TPassThroughColorShader m_shader;
    float m_angle;
    tmath::Vec3f m_cameraOffset;
    int m_direction;
public:
    TClippingRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};