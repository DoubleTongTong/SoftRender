#pragma once
#include <stdint.h>

class TRasterizer
{
public:
	TRasterizer();
	TRasterizer(uint32_t* pBits, int width, int height);

	int GetWidth() const;
	int GetHeight() const;

	void SetPixel(int x, int y, uint32_t color);
	void Clear(uint32_t color);

	static inline uint32_t MakeRGB(uint8_t r, uint8_t g, uint8_t b)
	{
		return (uint32_t)(b | (g << 8) | (r << 16));
	}
private:
	uint32_t* m_pBits;  // raw pixel data
	int       m_width;
	int       m_height;

public:
	TRasterizer(TRasterizer&& other) noexcept;
	TRasterizer& operator=(TRasterizer&& other) noexcept;

	TRasterizer(const TRasterizer&) = delete;
	TRasterizer& operator=(const TRasterizer&) = delete;
};