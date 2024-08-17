#include "TModelRenderTask.h"

TModelRenderTask::TModelRenderTask(TBasicWindow& win)
	: m_camera(tmath::Vec3f(0.0f, 0.0f, -5.0f), tmath::Vec3f(0.0f, 0.0f, 0.0f)),
	  m_model(win.GetRenderer(), "model/Rampaging T-Rex.glb"),
	  m_angle(0.0f)
{
	TSoftRenderer& sr = win.GetRenderer();
	////
	int width = win.GetWindowWidth();
	int height = win.GetWindowHeight();

	float aspect = (float)width / height;

	m_shader.projectionMatrix = tmath::PerspectiveMatrix(tmath::degToRad(60.0f), aspect, 0.1f, 100.0f);
	m_shader.viewMatrix = tmath::TranslationMatrix(0.0f, 0.0f, 4.0f);
	m_shader.modelMatrix.ToIdentity();

	m_shader.lightDirection = { -1.0f, -0.5f, 0.7f };
	m_shader.lightDirection.Normalize();
	m_shader.lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_shader.ambientColor = { 0.5f, 0.5f, 0.5f, 1.0f };

	sr.UseProgram(&m_shader);

	////
	sr.Enable(TEnableCap::DepthTest);
	sr.DepthFunc(TDepthFunc::Less);
	////
	sr.Enable(TEnableCap::CullFace);
	sr.CullFace(TCullFace::Back);
	sr.FrontFace(TFrontFace::CounterClockwise);
	////
	win.AddInputHandler(&m_camera);
}

void TModelRenderTask::Render(TSoftRenderer& sr)
{
	m_shader.viewMatrix = m_camera.GetViewMatrix();
	sr.ClearColor({ 255,255,255 });
	sr.ClearDepth(1.0f);

	tmath::Mat4f rotateMatrix = tmath::RotationMatrix({ 0.0f, 1.0f, 0.0f }, m_angle);
	tmath::Mat4f translateMatrix = tmath::TranslationMatrix(0.0f, -3.5f, 4.0f);
	//tmath::Mat4f scaleMatrix = tmath::ScaleMatrix(0.1f, 0.1f, 0.1f);
	m_angle -= 0.1f;

	m_model.Draw(translateMatrix * rotateMatrix, &m_shader);
}