#include "TLambertianRenderTask.h"

TLambertianRenderTask::TLambertianRenderTask(TBasicWindow& win)
	: m_camera(tmath::Vec3f(0.0f, 0.0f, -4.0f), tmath::Vec3f(0.0f, 0.0f, 0.0f))
{
	float vertices[] =
	{
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	uint32_t indices[] =
	{
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12,13,14,15,16,17,
		18,19,20,21,22,23,
		24,25,26,27,28,29,
		30,31,32,33,34,35
	};

	TSoftRenderer& sr = win.GetRenderer();

	uint32_t vao, vbo, ebo;
	sr.GenVertexArrays(1, &vao);
	sr.BindVertexArray(vao);

	sr.GenBuffers(1, &vbo);
	sr.BindBuffer(TBufferType::ArrayBuffer, vbo);
	sr.BufferData(TBufferType::ArrayBuffer, sizeof(vertices), vertices);

	sr.VertexAttribPointer(0, 3, 8 * sizeof(float), 0);
	sr.VertexAttribPointer(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	sr.VertexAttribPointer(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	sr.GenBuffers(1, &ebo);
	sr.BindBuffer(TBufferType::ElementArrayBuffer, ebo);
	sr.BufferData(TBufferType::ElementArrayBuffer, sizeof(indices), indices);

	sr.PrintVAO(vao);
	////
	uint32_t textureId;
	sr.GenTextures(1, &textureId);
	sr.BindTexture(textureId);

	TImage img("image/dog.jpg", TImage::ColorFormat::RGBA);
	sr.TexImage2D(img.GetWidth(), img.GetHeight(), img.GetData());

	sr.TexParameter(TTextureParam::WrapS, (int)TTextureWrapMode::Repeat);
	sr.TexParameter(TTextureParam::WrapT, (int)TTextureWrapMode::Repeat);
	sr.TexParameter(TTextureParam::Filter, (int)TTextureFilterMode::Nearest);
	////
	int width = win.GetWindowWidth();
	int height = win.GetWindowHeight();

	float aspect = (float)width / height;

	m_shader.projectionMatrix = tmath::PerspectiveMatrix(tmath::degToRad(60.0f), aspect, 0.1f, 100.0f);
	m_shader.viewMatrix = tmath::TranslationMatrix(0.0f, 0.0f, 4.0f);
	m_shader.modelMatrix.ToIdentity();

	m_shader.lightDirection = { -1.0f, -0.3f, 0.7f };
	m_shader.lightDirection.Normalize();
	m_shader.lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_shader.ambientColor = { 0.1f, 0.1f, 0.1f, 1.0f };

	sr.UseProgram(&m_shader);

	////
	sr.Enable(TEnableCap::DepthTest);
	sr.DepthFunc(TDepthFunc::Less);

	////
	win.AddInputHandler(&m_camera);
}

void TLambertianRenderTask::Render(TSoftRenderer& sr)
{
	m_shader.viewMatrix = m_camera.GetViewMatrix();
	sr.ClearColor({ 0,0,0 });
	sr.ClearDepth(1.0f);

	sr.DrawElements(TDrawMode::Triangles, 36, 0);
}