#include "TRasterizer.h"
#include <string.h>

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

void TRasterizer::SetPixel(int x, int y, uint32_t color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return;

	m_pBits[y * m_width + x] = color;
}

void TRasterizer::Clear(uint32_t color)
{
	for (int i = 0; i < m_width * m_height; i++)
	{
		m_pBits[i] = color;
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