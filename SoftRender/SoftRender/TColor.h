#pragma once
#include <stdint.h>

struct BGRA
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t a;
};

class TRGBA
{
public:
	uint8_t r, g, b, a;

public:
	TRGBA();
	TRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	TRGBA(const BGRA* bgra);
	TRGBA Lerp(const TRGBA& other, float t) const;
	uint32_t ToBGR888() const;

	static TRGBA Interpolate(const TRGBA& color1, float w1,
		const TRGBA& color2, float w2,
		const TRGBA& color3, float w3);
};