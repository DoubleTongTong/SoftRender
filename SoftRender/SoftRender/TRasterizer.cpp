#include "TRasterizer.h"
#include <string.h>
#include <algorithm>
#include <limits>

TRasterizer::TRasterizer()
	: TRasterizer(NULL, 0, 0)
{
}

TRasterizer::TRasterizer(uint32_t* pBits, int width, int height)
	: m_pBits(pBits),
	  m_width(width),
	  m_height(height)
{
}

int TRasterizer::GetWidth() const
{
	return m_width;
}

int TRasterizer::GetHeight() const
{
	return m_height;
}

void TRasterizer::SetPixel(int x, int y, TRGBA color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return;

	if (m_state.IsBlendEnabled())
		BlendPixel(x, y, color.r, color.g, color.b, color.a);
	else
		m_pBits[y * m_width + x] = color.ToBGR888();
}

void TRasterizer::SetPixel(int x, int y, BGRA* color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return;

	if (m_state.IsBlendEnabled())
		BlendPixel(x, y, color->r, color->g, color->b, color->a);
	else
		m_pBits[y * m_width + x] = *reinterpret_cast<uint32_t*>(color);
}

void TRasterizer::DrawLine(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2)
{
	DrawLineBresenham(x1, y1, color1, x2, y2, color2);
}

void TRasterizer::DrawLineDifferential(int x1, int y1, int x2, int y2)
{
	int numSteps;
	float deltaX, deltaY;

	int dx = x2 - x1;
	int dy = y2 - y1;
	float k = (dx == 0) ? std::numeric_limits<float>::infinity() : (float)dy / (float)dx;

	if (dx == 0)
	{
		deltaX = 0;
		deltaY = dy >= 0 ? 1.0f : -1.0f;
		numSteps = abs(dy);
	}
	else if (fabsf(k) <= 1)
	{
		deltaX = dx >= 0 ? 1.0f : -1.0f;
		deltaY = deltaX * k;
		numSteps = abs(dx);
	}
	else
	{
		deltaY = dy >= 0 ? 1.0f : -1.0f;
		deltaX = deltaY / k;
		numSteps = abs(dy);
	}

	float x = (float)x1, y = (float)y1;
	for (int i = 0; i <= numSteps; i++)
	{
		SetPixel((int)round(x), (int)round(y), TRGBA(0, 0, 0));
		x += deltaX;
		y += deltaY;
	}
}

void TRasterizer::DrawLineBresenham(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2)
{
	bool useSwappedXY = std::abs(y2 - y1) > std::abs(x2 - x1);

	// 如果线段斜率绝对值大于 1，则交换 x 和 y
	if (useSwappedXY)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
		std::swap(color1, color2);
	}

	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	int E = 2 * std::abs(deltaY) - deltaX;

	int y = y1;
	int yStep = y1 < y2 ? 1 : -1;

	for (int x = x1; x <= x2; x++)
	{
		float t = deltaX == 0 ? 0 : (float)(x - x1) / (float)deltaX;
		TRGBA interpolatedColor = color1.Lerp(color2, t);

		if (useSwappedXY)
			SetPixel(y, x, interpolatedColor);
		else
			SetPixel(x, y, interpolatedColor);

		if (E < 0)
		{
			E += 2 * std::abs(deltaY);
		}
		else
		{
			E += 2 * (std::abs(deltaY) - deltaX);
			y += yStep;
		}
	}
}

void TRasterizer::DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
	TRGBA color1, TRGBA color2, TRGBA color3)
{
	int minX = std::min(p1.x(), std::min(p2.x(), p3.x()));
	int maxX = std::max(p1.x(), std::max(p2.x(), p3.x()));
	int minY = std::min(p1.y(), std::min(p2.y(), p3.y()));
	int maxY = std::max(p1.y(), std::max(p2.y(), p3.y()));

	tmath::Vec2i p, pp1, pp2, pp3;
	int c1, c2, c3;
	float area = (float)std::abs(tmath::cross(p2 - p1, p3 - p1));

	for (int i = minX; i <= maxX; i++)
	{
		p.x() = i;
		for (int j = minY; j <= maxY; j++)
		{
			p.y() = j;

			pp1.x() = p1.x() - p.x(); pp1.y() = p1.y() - p.y(); // pp1 = p1 - p;
			pp2.x() = p2.x() - p.x(); pp2.y() = p2.y() - p.y(); // pp2 = p2 - p;
			pp3.x() = p3.x() - p.x(); pp3.y() = p3.y() - p.y(); // pp3 = p3 - p;

			c1 = tmath::cross(pp1, pp2);
			c2 = tmath::cross(pp2, pp3);
			c3 = tmath::cross(pp3, pp1);

			if ((c1 >= 0 && c2 >= 0 && c3 >= 0) ||
				(c1 <= 0 && c2 <= 0 && c3 <= 0))
			{
				TRGBA color = TRGBA::Interpolate(
					color1, std::abs(c2) / area,
					color2, std::abs(c3) / area,
					color3, std::abs(c1) / area);
				SetPixel(i, j, color);
			}
		}
	}
}

void TRasterizer::DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
	const tmath::UV2f& uv1, const tmath::UV2f& uv2, const tmath::UV2f& uv3)
{
	int minX = std::min(p1.x(), std::min(p2.x(), p3.x()));
	int maxX = std::max(p1.x(), std::max(p2.x(), p3.x()));
	int minY = std::min(p1.y(), std::min(p2.y(), p3.y()));
	int maxY = std::max(p1.y(), std::max(p2.y(), p3.y()));

	tmath::Vec2i p, pp1, pp2, pp3;
	int c1, c2, c3;
	tmath::UV2f uv;
	float alpha, beta, gamma;
	float area = (float)std::abs(tmath::cross(p2 - p1, p3 - p1));

	for (int i = minX; i <= maxX; i++)
	{
		p.x() = i;
		for (int j = minY; j <= maxY; j++)
		{
			p.y() = j;

			pp1.x() = p1.x() - p.x(); pp1.y() = p1.y() - p.y(); // pp1 = p1 - p;
			pp2.x() = p2.x() - p.x(); pp2.y() = p2.y() - p.y(); // pp2 = p2 - p;
			pp3.x() = p3.x() - p.x(); pp3.y() = p3.y() - p.y(); // pp3 = p3 - p;

			c1 = tmath::cross(pp1, pp2);
			c2 = tmath::cross(pp2, pp3);
			c3 = tmath::cross(pp3, pp1);

			if ((c1 >= 0 && c2 >= 0 && c3 >= 0) ||
				(c1 <= 0 && c2 <= 0 && c3 <= 0))
			{
				alpha = std::abs(c2) / area;
				beta = std::abs(c3) / area;
				gamma = std::abs(c1) / area;

				uv.u() = uv1.u() * alpha + uv2.u() * beta + uv3.u() * gamma;
				uv.v() = uv1.v() * alpha + uv2.v() * beta + uv3.v() * gamma;

				SetPixel(i, j, SampleTexture(uv));
			}
		}
	}
}

void TRasterizer::DrawImage(const TImage& image, int startX, int startY)
{
	int x, y;
	BGRA* data = (BGRA*)image.GetData();

	for (int h = 0; h < image.GetHeight(); h++)
	{
		y = startY + h;
		for (int w = 0; w < image.GetWidth(); w++)
		{
			x = startX + w;
			SetPixel(x, y, data + h * image.GetWidth() + w);
		}
	}
}

void TRasterizer::BlendPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	BGRA* dstPixel = reinterpret_cast<BGRA*>(&m_pBits[y * m_width + x]);

	float srcAlpha = a / 255.0f;
	float dstAlpha = 1.0f - srcAlpha;

	dstPixel->b = (b * srcAlpha + dstPixel->b * dstAlpha);
	dstPixel->g = (g * srcAlpha + dstPixel->g * dstAlpha);
	dstPixel->r = (r * srcAlpha + dstPixel->r * dstAlpha);
}

BGRA* TRasterizer::SampleTexture(const tmath::UV2f& uv)
{
	const TImage* m_texture = m_state.GetTexture();

	int w = m_texture->GetWidth();
	int h = m_texture->GetHeight();

	int x = static_cast<int>(uv.u() * w) % (w - 1);
	int y = static_cast<int>(uv.v() * h) % (h - 1);
	BGRA* data = (BGRA*)m_texture->GetData();
	return (data + y * w + x);
}

void TRasterizer::Clear(TRGBA color)
{
	for (int i = 0; i < m_width * m_height; i++)
	{
		m_pBits[i] = color.ToBGR888();
	}
}

void TRasterizer::SetBlend(bool enable)
{
	m_state.SetBlend(enable);
}

void TRasterizer::SetTexture(const TImage* texture)
{
	m_state.SetTexture(texture);
}

TRasterizer::TRasterizer(TRasterizer&& other) noexcept
	: m_pBits(other.m_pBits),
	  m_width(other.m_width),
	  m_height(other.m_height),
	  m_state()
{
}

TRasterizer& TRasterizer::operator=(TRasterizer&& other) noexcept
{
	if (this != &other)
	{
		m_pBits = other.m_pBits;
		m_width = other.m_width;
		m_height = other.m_height;
	}

	return *this;
}