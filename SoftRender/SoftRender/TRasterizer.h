#pragma once
#include "TColor.h"
#include "TVector.h"

class TRasterizer
{
public:
	TRasterizer();
	TRasterizer(uint32_t* pBits, int width, int height);

	int GetWidth() const;
	int GetHeight() const;

	void SetPixel(int x, int y, TRGB888 color);
	void DrawLine(int x1, int y1, TRGB888 color1, int x2, int y2, TRGB888 color2);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		TRGB888 color1, TRGB888 color2, TRGB888 color3);
	void Clear(TRGB888 color);

private:
	uint32_t* m_pBits;  // raw pixel data
	int       m_width;
	int       m_height;

	void DrawLineDifferential(int x1, int y1, int x2, int y2);
	void DrawLineBresenham(int x1, int y1, TRGB888 color1, int x2, int y2, TRGB888 color);

public:
	TRasterizer(TRasterizer&& other) noexcept;
	TRasterizer& operator=(TRasterizer&& other) noexcept;

	TRasterizer(const TRasterizer&) = delete;
	TRasterizer& operator=(const TRasterizer&) = delete;
};