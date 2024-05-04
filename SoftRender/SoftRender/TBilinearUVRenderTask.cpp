#include "TBilinearUVRenderTask.h"

TBilinearUVRenderTask::TBilinearUVRenderTask(TBasicWindow& win)
	: m_texture("image/dog.jpg")
{
	int maxWidth = win.GetWindowWidth();
	int maxHeight = win.GetWindowHeight();

	int textureWidth = m_texture.GetWidth();
	int textureHeight = m_texture.GetHeight();

	float scale = std::min(
		maxWidth / (float)textureWidth,
		maxHeight / (float)textureHeight);
	int width = (int)(textureWidth * scale);
	int height = (int)(textureHeight * scale);

	p1 = tmath::Point2i(0, 0);
	p2 = tmath::Point2i(width, 0);
	p3 = tmath::Point2i(0, height);
	p4 = tmath::Point2i(width, height);

	uv1 = tmath::UV2f(0.0f, 0.0f);
	uv2 = tmath::UV2f(1.0f, 0.0f);
	uv3 = tmath::UV2f(0.0f, 1.0f);
	uv4 = tmath::UV2f(1.0f, 1.0f);
}

void TBilinearUVRenderTask::Render(TRasterizer& rz)
{
	rz.SetTexture(&m_texture);
	rz.SetSampleMode(TSampleMode::Bilinear);

	rz.DrawTriangle(p1, p2, p3, uv1, uv2, uv3);
	rz.DrawTriangle(p2, p3, p4, uv2, uv3, uv4);
}