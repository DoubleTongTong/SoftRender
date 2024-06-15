#pragma once

#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TPassThroughUvShader.h"

class TChessboardRenderTask : public IRenderTask
{
    TImage m_texture;
    TPassThroughUvShader m_shader;
    float m_angle;

public:
    TChessboardRenderTask(TBasicWindow& win);
    virtual void Render(TSoftRenderer& sr) override;

private:
    void Transform();
};