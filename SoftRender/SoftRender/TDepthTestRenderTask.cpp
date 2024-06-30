#include "TDepthTestRenderTask.h"

TDepthTestRenderTask::TDepthTestRenderTask(TBasicWindow& win)
{
    float vertices[] = {
        // 第一个三角形
        -0.5f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,
        0.25f, 0.5f, 0.0f,

        // 第二个三角形
        0.3f, 0.0f, 0.3f,
        0.8f, 0.0f, 0.3f,
        0.45f, 0.5f, 0.3f,
    };

    float colors[] = {
        // 第一个三角形
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        // 第二个三角形
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
    };

    uint32_t indices[] = {
        // 第一个三角形
        0, 1, 2,

        // 第二个三角形
        3, 4, 5,
    };

    TSoftRenderer& sr = win.GetRenderer();

    uint32_t vao, vboPosition, vboColor, vboUv, ebo;
    sr.GenVertexArrays(1, &vao);
    sr.BindVertexArray(vao);

    sr.GenBuffers(1, &vboPosition);
    sr.BindBuffer(TBufferType::ArrayBuffer, vboPosition);
    sr.BufferData(TBufferType::ArrayBuffer, sizeof(vertices), vertices);
    sr.VertexAttribPointer(0, 3, 3 * sizeof(float), 0);

    sr.GenBuffers(1, &vboColor);
    sr.BindBuffer(TBufferType::ArrayBuffer, vboColor);
    sr.BufferData(TBufferType::ArrayBuffer, sizeof(colors), colors);
    sr.VertexAttribPointer(1, 4, 4 * sizeof(float), 0);

    sr.GenBuffers(1, &ebo);
    sr.BindBuffer(TBufferType::ElementArrayBuffer, ebo);
    sr.BufferData(TBufferType::ElementArrayBuffer, sizeof(indices), indices);

    sr.PrintVAO(vao);

    ////
    int width = win.GetWindowWidth();
    int height = win.GetWindowHeight();

    float aspect = (float)width / height;

    m_shader.projectionMatrix = tmath::PerspectiveMatrix(tmath::degToRad(60.0f), aspect, 0.1f, 100.0f);
    m_shader.viewMatrix = tmath::TranslationMatrix(0.0f, 0.0f, 2.0f);
    m_shader.modelMatrix.ToIdentity();

    sr.UseProgram(&m_shader);

    ////
    sr.Enable(TEnableCap::DepthTest);
    sr.DepthFunc(TDepthFunc::Less);
}


void TDepthTestRenderTask::Render(TSoftRenderer& sr)
{
    sr.ClearColor({ 0,0,0 });
    sr.ClearDepth(1.0f);

    sr.DrawElements(TDrawMode::Triangles, 3, 0);
    sr.DrawElements(TDrawMode::Triangles, 3, 3 * sizeof(uint32_t));
}