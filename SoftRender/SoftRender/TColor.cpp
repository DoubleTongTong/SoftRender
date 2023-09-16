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