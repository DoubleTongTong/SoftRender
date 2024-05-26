#include "TTriangleOGLPipelineRenderTask.h"

TTriangleOGLPipelineRenderTask::TTriangleOGLPipelineRenderTask(TBasicWindow& win)
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };

    float uvs[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f
    };

    uint32_t indices[] = {
        0, 1, 2
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

    sr.GenBuffers(1, &vboUv);
    sr.BindBuffer(TBufferType::ArrayBuffer, vboUv);
    sr.BufferData(TBufferType::ArrayBuffer, sizeof(uvs), uvs);
    sr.VertexAttribPointer(2, 2, 2 * sizeof(float), 0);

    sr.GenBuffers(1, &ebo);
    sr.BindBuffer(TBufferType::ElementArrayBuffer, ebo);
    sr.BufferData(TBufferType::ElementArrayBuffer, sizeof(indices), indices);

    sr.PrintVAO(vao);
}

void TTriangleOGLPipelineRenderTask::Render(TSoftRenderer& sr)
{

}