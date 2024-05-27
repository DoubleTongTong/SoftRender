#pragma once
#include "TColor.h"
#include "TVector.h"
#include "TImage.h"
#include "TRenderState.h"
#include "TShader.h"

class TRasterizer
{
public:
	TRasterizer();
	TRasterizer(uint32_t* pBits, int width, int height, TRenderState* m_state);

	int GetWidth() const;
	int GetHeight() const;

	void SetPixel(int x, int y, TRGBA color);
	void SetPixel(int x, int y, BGRA* color);
	void DrawLine(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		TRGBA color1, TRGBA color2, TRGBA color3);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		const tmath::UV2f& uv1, const tmath::UV2f& uv2, const tmath::UV2f& uv3);
	void DrawImage(const TImage& image, int startX, int startY);
	void Clear(TRGBA color);

	void RasterizeTriangle(
		const TVertexShaderOutput& v1,
		const TVertexShaderOutput& v2,
		const TVertexShaderOutput& v3,
		FragmentShaderFunction fragShader);

private:
	uint32_t* m_pBits;  // raw pixel data
	int       m_width;
	int       m_height;

	TRenderState* m_state;

private:
	void DrawLineDifferential(int x1, int y1, int x2, int y2);
	void DrawLineBresenham(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color);

	void BlendPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	BGRA* SampleTextureNearest(const tmath::UV2f& uv);
	TRGBA SampleTextureBilinear(const tmath::UV2f& uv);

	tmath::UV2f AdjustUV(const tmath::UV2f& uv);
public:
	TRasterizer(TRasterizer&& other) noexcept;
	TRasterizer& operator=(TRasterizer&& other) noexcept;

	TRasterizer(const TRasterizer&) = delete;
	TRasterizer& operator=(const TRasterizer&) = delete;
};