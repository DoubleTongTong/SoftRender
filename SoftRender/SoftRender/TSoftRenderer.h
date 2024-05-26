#pragma once

#include "TRasterizer.h"

class TSoftRenderer
{
public:
	TSoftRenderer();
	void SetRasterizer(uint32_t* pBits, int width, int height);
	int GetRenderWidth();
	int GetRenderHeight();

public:
	void SetBlend(bool enable);
	void SetTexture(const TImage* texture);
	void SetSampleMode(TSampleMode mode);
	void SetWrapMode(TWrapMode mode);

private:
	TRenderState m_state;
	TRasterizer  m_rz;

public:
	TSoftRenderer(TSoftRenderer&& other) noexcept = default;
	TSoftRenderer& operator=(TSoftRenderer&& other) = default;

	TSoftRenderer(const TSoftRenderer&) = delete;
	TSoftRenderer& operator=(const TSoftRenderer&) = delete;

public:
	void Clear(TRGBA color);
	void SetPixel(int x, int y, TRGBA color);
	void DrawLine(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		TRGBA color1, TRGBA color2, TRGBA color3);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		const tmath::UV2f& uv1, const tmath::UV2f& uv2, const tmath::UV2f& uv3);
	void DrawImage(const TImage& image, int startX, int startY);
};