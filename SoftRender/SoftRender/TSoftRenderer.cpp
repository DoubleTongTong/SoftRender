#include "TSoftRenderer.h"

TSoftRenderer::TSoftRenderer()
{
}

void TSoftRenderer::SetRasterizer(uint32_t* pBits, int width, int height)
{
	m_rz = TRasterizer(pBits, width, height, &m_state);
}

int TSoftRenderer::GetRenderWidth()
{
	return m_rz.GetWidth();
}

int TSoftRenderer::GetRenderHeight()
{
	return m_rz.GetHeight();
}

void TSoftRenderer::Clear(TRGBA color)
{
	m_rz.Clear(color);
}

void TSoftRenderer::SetPixel(int x, int y, TRGBA color)
{
	m_rz.SetPixel(x, y, color);
}

void TSoftRenderer::DrawLine(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2)
{
	m_rz.DrawLine(x1, y1, color1, x2, y2, color2);
}

void TSoftRenderer::DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
	TRGBA color1, TRGBA color2, TRGBA color3)
{
	m_rz.DrawTriangle(p1, p2, p3, color1, color2, color3);
}

void TSoftRenderer::DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
	const tmath::UV2f& uv1, const tmath::UV2f& uv2, const tmath::UV2f& uv3)
{
	m_rz.DrawTriangle(p1, p2, p3, uv1, uv2, uv3);
}

void TSoftRenderer::DrawImage(const TImage& image, int startX, int startY)
{
	m_rz.DrawImage(image, startX, startY);
}

void TSoftRenderer::SetBlend(bool enable)
{
	m_state.SetBlend(enable);
}

void TSoftRenderer::SetTexture(const TImage* texture)
{
	m_state.SetTexture(texture);
}

void TSoftRenderer::SetSampleMode(TSampleMode mode)
{
	m_state.SetSampleMode(mode);
}

void TSoftRenderer::SetWrapMode(TWrapMode mode)
{
	m_state.SetWrapMode(mode);
}