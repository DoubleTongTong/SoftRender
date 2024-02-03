#include "TColor.h"

TRGB888::TRGB888()
	: r(0), g(0), b(0)
{
}

TRGB888::TRGB888(uint8_t r, uint8_t g, uint8_t b)
	: r(r), g(g), b(b)
{
}

uint32_t TRGB888::ToBGR888() const
{
	return ((uint32_t)b |
		   ((uint32_t)g << 8) |
		   ((uint32_t)r << 16));
}

TRGB888 TRGB888::Lerp(const TRGB888& other, float t) const
{
	return TRGB888(
		(uint8_t)(r + t * (other.r - r)),
		(uint8_t)(g + t * (other.g - g)),
		(uint8_t)(b + t * (other.b - b))
	);
}

TRGB888 TRGB888::Interpolate(const TRGB888& color1, float w1,
	const TRGB888& color2, float w2,
	const TRGB888& color3, float w3)
{
	return TRGB888(
		(uint8_t)(color1.r * w1 + color2.r * w2 + color3.r * w3),
		(uint8_t)(color1.g * w1 + color2.g * w2 + color3.g * w3),
		(uint8_t)(color1.b * w1 + color2.b * w2 + color3.b * w3)
	);
}