#pragma once

#include <stdint.h>
#include "TVector.h"
#include "TColor.h"

enum class TTextureParam
{
	WrapS,
	WrapT,
	Filter,
};

enum class TTextureWrapMode
{
	MirroredRepeat,
	Repeat,
};

enum class TTextureFilterMode
{
	Nearest,
	Linear,
};

class TTexture
{
public:
	TTexture(uint32_t id);
	~TTexture();

	void SetTextureData(uint32_t width, uint32_t height, void* data);
	void SetParameter(TTextureParam param, int value);

	tmath::Vec4f Sample(const tmath::Vec2f& uv) const;
private:
	float AdjustCoordinate(float coord, TTextureWrapMode wrapMode) const;
	tmath::Vec2f AdjustUV(const tmath::Vec2f& uv) const;
	tmath::Vec4f SampleNearest(const tmath::Vec2f& uv) const;
	tmath::Vec4f SampleBilinear(const tmath::Vec2f& uv) const;

private:
	uint32_t m_id;
	uint32_t m_size;
	uint32_t m_width;
	uint32_t m_height;
	TRGBA* m_pTextureData;

	TTextureWrapMode m_wrapS;
	TTextureWrapMode m_wrapT;
	TTextureFilterMode m_filter;
};