#pragma once
#include <stdint.h>

class TRGB888
{
public:
	uint8_t r, g, b;

public:
	TRGB888();
	TRGB888(uint8_t r, uint8_t g, uint8_t b);
	TRGB888 Lerp(const TRGB888& other, float t) const;
	uint32_t ToBGR888() const;
};