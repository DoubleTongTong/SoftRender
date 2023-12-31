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

void TRasterizer::SetPixel(int x, int y, TRGB888 color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return;

	m_pBits[y * m_width + x] = color.ToBGR888();
}

void TRasterizer::DrawLine(int x1, int y1, TRGB888 color1, int x2, int y2, TRGB888 color2)
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
		deltaY = dy >= 0 ? 1 : -1;
		numSteps = abs(dy);
	}
	else if (fabsf(k) <= 1)
	{
		deltaX = dx >= 0 ? 1 : -1;
		deltaY = deltaX * k;
		numSteps = abs(dx);
	}
	else
	{
		deltaY = dy >= 0 ? 1 : -1;
		deltaX = deltaY / k;
		numSteps = abs(dy);
	}

	float x = x1, y = y1;
	for (int i = 0; i <= numSteps; i++)
	{
		SetPixel(round(x), round(y), TRGB888(0, 0, 0));
		x += deltaX;
		y += deltaY;
	}
}

void TRasterizer::DrawLineBresenham(int x1, int y1, TRGB888 color1, int x2, int y2, TRGB888 color2)
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
		TRGB888 interpolatedColor = color1.Lerp(color2, t);

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

void TRasterizer::Clear(TRGB888 color)
{
	for (int i = 0; i < m_width * m_height; i++)
	{
		m_pBits[i] = color.ToBGR888();
	}
}

TRasterizer::TRasterizer(TRasterizer&& other) noexcept
	: m_pBits(other.m_pBits),
	  m_width(other.m_width),
	  m_height(other.m_height)
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