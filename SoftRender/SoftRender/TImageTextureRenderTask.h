#pragma once

#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughUvShader.h"

class TImageTextureRenderTask : public IRenderTask
{
    TPassThroughUvShader m_shader;
    float m_angle;

public:
    TImageTextureRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};