#pragma once
#include "IRenderTask.h"
#include "TBasicWindow.h"
#include "TMatrix.h"
#include <array>

class TViewTransformRenderTask : public IRenderTask
{
    tmath::Mat4f m_modelMatrix, m_viewMatrix;
    tmath::Mat4f m_perspectiveMatrix, m_orthographicMatrix;
    tmath::Mat4f m_screenMatrix;

    std::array<tmath::Vec4f, 36> m_cubeVertices;
    tmath::Point2i m_screenPoints[36];

    float m_angle, m_cameraPos;
public:
    TViewTransformRenderTask(TBasicWindow& win);
    virtual void Render(TRasterizer& rz) override;

private:
    void Transform();
};