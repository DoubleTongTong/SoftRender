#include "TViewTransformRenderTask.h"

TViewTransformRenderTask::TViewTransformRenderTask(TBasicWindow& win)
	: m_angle(0), m_cameraPos(-5.0f)
{
	int width = win.GetWindowWidth();
	int height = win.GetWindowHeight();

	float aspect = (float)width / height;
	m_screenMatrix = tmath::ScreenMatrix<float>(width, height);
	m_perspectiveMatrix = tmath::PerspectiveMatrix(tmath::degToRad(60.0f), aspect, 0.1f, 100.0f);
	m_orthographicMatrix = tmath::OrthographicMatrix(-3 * aspect, 3 * aspect, -3.0f, 3.0f, 0.1f, 100.0f);

	m_cubeVertices = { {
		{-0.5f, -0.5f, -0.5f, 1.0f},
		{ 0.5f, -0.5f, -0.5f, 1.0f},
		{ 0.5f,  0.5f, -0.5f, 1.0f},
		{ 0.5f,  0.5f, -0.5f, 1.0f},
		{-0.5f,  0.5f, -0.5f, 1.0f},
		{-0.5f, -0.5f, -0.5f, 1.0f},

		{-0.5f, -0.5f,  0.5f, 1.0f},
		{ 0.5f, -0.5f,  0.5f, 1.0f},
		{ 0.5f,  0.5f,  0.5f, 1.0f},
		{ 0.5f,  0.5f,  0.5f, 1.0f},
		{-0.5f,  0.5f,  0.5f, 1.0f},
		{-0.5f, -0.5f,  0.5f, 1.0f},

		{-0.5f,  0.5f,  0.5f, 1.0f},
		{-0.5f,  0.5f, -0.5f, 1.0f},
		{-0.5f, -0.5f, -0.5f, 1.0f},
		{-0.5f, -0.5f, -0.5f, 1.0f},
		{-0.5f, -0.5f,  0.5f, 1.0f},
		{-0.5f,  0.5f,  0.5f, 1.0f},

		{0.5f,  0.5f,  0.5f, 1.0f},
		{0.5f,  0.5f, -0.5f, 1.0f},
		{0.5f, -0.5f, -0.5f, 1.0f},
		{0.5f, -0.5f, -0.5f, 1.0f},
		{0.5f, -0.5f,  0.5f, 1.0f},
		{0.5f,  0.5f,  0.5f, 1.0f},

		{-0.5f, -0.5f, -0.5f, 1.0f},
		{ 0.5f, -0.5f, -0.5f, 1.0f},
		{ 0.5f, -0.5f,  0.5f, 1.0f},
		{ 0.5f, -0.5f,  0.5f, 1.0f},
		{-0.5f, -0.5f,  0.5f, 1.0f},
		{-0.5f, -0.5f, -0.5f, 1.0f},

		{-0.5f,  0.5f, -0.5f, 1.0f},
		{ 0.5f,  0.5f, -0.5f, 1.0f},
		{ 0.5f,  0.5f,  0.5f, 1.0f},
		{ 0.5f,  0.5f,  0.5f, 1.0f},
		{-0.5f,  0.5f,  0.5f, 1.0f},
		{-0.5f,  0.5f, -0.5f, 1.0f},
	} };
}

void TViewTransformRenderTask::Transform()
{
	m_angle += 0.01f;
	m_cameraPos -= 0.002f;
	m_modelMatrix = tmath::RotationMatrix(tmath::Vec3f(1.0f, 1.0f, 1.0f), m_angle);
	//m_viewMatrix = tmath::LookAtMatrix(tmath::Vec3f(0, 0, m_cameraPos), tmath::Vec3f(0, 0, 0), tmath::Vec3f(0, 1, 0));
	m_viewMatrix = tmath::TranslationMatrix(0.0f, 0.0f, m_cameraPos).Inverse();

	tmath::Vec4f vec;
	for (int i = 0; i < 36; i++)
	{
		vec = m_perspectiveMatrix * m_viewMatrix * m_modelMatrix * m_cubeVertices[i];
		//vec = m_orthographicMatrix * m_viewMatrix * m_modelMatrix * m_cubeVertices[i];
		vec /= vec.w();
		vec = m_screenMatrix * vec;

		m_screenPoints[i].x() = vec.x();
		m_screenPoints[i].y() = vec.y();
	}
}

void TViewTransformRenderTask::Render(TSoftRenderer& sr)
{
	Transform();
	sr.ClearColor({ 0,0,0 });
	for (int i = 0; i < 12; i++)
	{
		sr.DrawTriangle(m_screenPoints[3 * i], m_screenPoints[3 * i + 1], m_screenPoints[3 * i + 2],
			{ 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 });
	}
}