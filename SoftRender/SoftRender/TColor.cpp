#include "TColor.h"

TRGBA::TRGBA()
	: r(0), g(0), b(0), a(255)
{
}

TRGBA::TRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: r(r), g(g), b(b), a(a)
{
}

TRGBA::TRGBA(const BGRA* bgra)
	: r(bgra->r), g(bgra->g), b(bgra->b), a(bgra->a)
{
}

uint32_t TRGBA::ToBGR888() const
{
	return ((uint32_t)b |
		   ((uint32_t)g << 8) |
		   ((uint32_t)r << 16));
}

tmath::Vec4f TRGBA::ToVec4f() const
{
	return tmath::Vec4f(
		r / 255.0f,
		g / 255.0f,
		b / 255.0f,
		a / 255.0f);
}

TRGBA TRGBA::Lerp(const TRGBA& other, float t) const
{
	return TRGBA(
		(uint8_t)(r + t * (other.r - r)),
		(uint8_t)(g + t * (other.g - g)),
		(uint8_t)(b + t * (other.b - b))
	);
}

TRGBA TRGBA::Interpolate(const TRGBA& color1, float w1,
	const TRGBA& color2, float w2,
	const TRGBA& color3, float w3)
{
	return TRGBA(
		(uint8_t)(color1.r * w1 + color2.r * w2 + color3.r * w3),
		(uint8_t)(color1.g * w1 + color2.g * w2 + color3.g * w3),
		(uint8_t)(color1.b * w1 + color2.b * w2 + color3.b * w3)
	);
}

TRGBA TRGBA::FromVec4f(const tmath::Vec4f& color)
{
	return TRGBA(
		(uint8_t)(color.x() * 255),
		(uint8_t)(color.y() * 255),
		(uint8_t)(color.z() * 255),
		(uint8_t)(color.w() * 255)
	);
}