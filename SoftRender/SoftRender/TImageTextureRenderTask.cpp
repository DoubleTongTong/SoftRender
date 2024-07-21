#include "TImageTextureRenderTask.h"

TImageTextureRenderTask::TImageTextureRenderTask(TBasicWindow& win)
    : m_angle(0)
{
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };

    //float uvs[] = {
    //    0.0f, 0.0f,
    //    1.0f, 0.0f,
    //    1.0f, 1.0f,
    //    0.0f, 1.0f
    //};

	float uvs[] = {
	    0.0f, 1.0f,
	    1.0f, 1.0f,
	    1.0f, 0.0f,
	    0.0f, 0.0f
	};

    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0,
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

    ////
    int width = win.GetWindowWidth();
    int height = win.GetWindowHeight();

    float aspect = (float)width / height;

    m_shader.projectionMatrix = tmath::PerspectiveMatrix(tmath::degToRad(60.0f), aspect, 0.1f, 100.0f);
    m_shader.viewMatrix = tmath::TranslationMatrix(0.0f, 0.0f, 3.0f);

    sr.UseProgram(&m_shader);

    uint32_t textureId;
    sr.GenTextures(1, &textureId);
    sr.BindTexture(textureId);

#if 0
    const int textureSize = 8;  // 8x8
    std::vector<uint32_t> chessboardTexture(textureSize * textureSize);

    // 生成棋盘格纹理
    for (int y = 0; y < textureSize; ++y)
    {
        for (int x = 0; x < textureSize; ++x)
        {
            bool isBlack = (x + y) % 2 == 0;
            chessboardTexture[y * textureSize + x] = isBlack ? 0xFF000000 : 0xFFFFFFFF; // 黑色或白色
        }
    }

    sr.TexImage2D(8, 8, chessboardTexture.data());
#else
    TImage img("image/dog.jpg", TImage::ColorFormat::RGBA);
    sr.TexImage2D(img.GetWidth(), img.GetHeight(), img.GetData());
#endif

    sr.TexParameter(TTextureParam::WrapS, (int)TTextureWrapMode::Repeat);
    sr.TexParameter(TTextureParam::WrapT, (int)TTextureWrapMode::Repeat);
    sr.TexParameter(TTextureParam::Filter, (int)TTextureFilterMode::Nearest);
}

void TImageTextureRenderTask::Render(TSoftRenderer& sr)
{
    Transform();

    sr.ClearColor({ 0,0,0 });

    sr.DrawElements(TDrawMode::Triangles, 6, 0);
}

void TImageTextureRenderTask::Transform()
{
    m_angle -= 0.1f;
    m_shader.modelMatrix = tmath::RotationMatrix(tmath::Vec3f(0.0f, 1.0f, 0.0f), m_angle);
}