#include "TTexture.h"
#include <string.h>
#include <assert.h>

TTexture::TTexture(uint32_t id)
	: m_id(id), m_pTextureData(NULL),
	  m_width(0), m_height(0), m_size(0),
	  m_wrapS(TTextureWrapMode::Repeat),
	  m_wrapT(TTextureWrapMode::Repeat),
	  m_filter(TTextureFilterMode::Nearest)
{
}

TTexture::~TTexture()
{
	delete[] m_pTextureData;
}

void TTexture::SetTextureData(uint32_t width, uint32_t height, void* data)
{
	m_width = width;
	m_height = height;
	// For simplification, only store in RGBA format
	uint32_t size = width * height * 4;

	if (size > m_size)
	{
		delete[] m_pTextureData;
		m_pTextureData = new TRGBA[width * height];
	}

	m_size = size;

	if (data != NULL && size > 0)
	{
		memcpy(m_pTextureData, data, size);
	}
}

void TTexture::SetParameter(TTextureParam param, int value)
{
	switch (param)
	{
	case TTextureParam::WrapS:
		m_wrapS = static_cast<TTextureWrapMode>(value);
		break;
	case TTextureParam::WrapT:
		m_wrapT = static_cast<TTextureWrapMode>(value);
		break;
	case TTextureParam::Filter:
		m_filter = static_cast<TTextureFilterMode>(value);
		break;
	default:
		assert(false);
	}
}

float TTexture::AdjustCoordinate(float coord, TTextureWrapMode wrapMode) const
{
	switch (wrapMode)
	{
	case TTextureWrapMode::MirroredRepeat:
		return 1.0f - std::abs(std::fmod(std::fmod(coord, 2.0f) + 2.0f, 2.0f) - 1.0f);
	case TTextureWrapMode::Repeat:
	default:
		return std::fmod(std::fmod(coord, 1.0f) + 1.0f, 1.0f);
	}
}

tmath::Vec2f TTexture::AdjustUV(const tmath::Vec2f& uv) const
{
	float u = AdjustCoordinate(uv.x(), m_wrapS);
	float v = AdjustCoordinate(uv.y(), m_wrapT);
	return tmath::Vec2f(u, v);
}

tmath::Vec4f TTexture::SampleNearest(const tmath::Vec2f& uv) const
{
	tmath::Vec2f adjustedUV = AdjustUV(uv);

	int x = static_cast<int>(adjustedUV.x() * (m_width - 1));
	int y = static_cast<int>(adjustedUV.y() * (m_height - 1));
	TRGBA* data = m_pTextureData + (y * m_width + x);

	return data->ToVec4f();
}

tmath::Vec4f TTexture::SampleBilinear(const tmath::Vec2f& uv) const
{
	tmath::Vec2f adjustedUV = AdjustUV(uv);

	float fx = adjustedUV.x() * (m_width - 1);
	float fy = adjustedUV.y() * (m_height - 1);

	int left = static_cast<int>(std::floor(fx));
	int right = static_cast<int>(std::ceil(fx));
	int top = static_cast<int>(std::floor(fy));
	int bottom = static_cast<int>(std::ceil(fy));

	float lerpX = fx - left;
	float lerpY = fy - top;

	TRGBA topLeft = m_pTextureData[top * m_width + left];
	TRGBA topRight = m_pTextureData[top * m_width + right];
	TRGBA bottomLeft = m_pTextureData[bottom * m_width + left];
	TRGBA bottomRight = m_pTextureData[bottom * m_width + right];

	TRGBA interpTop = topLeft.Lerp(topRight, lerpX);
	TRGBA interpBottom = bottomLeft.Lerp(bottomRight, lerpY);

	return interpTop.Lerp(interpBottom, lerpY).ToVec4f();
}

tmath::Vec4f TTexture::Sample(const tmath::Vec2f& uv) const
{
	switch (m_filter)
	{
	case TTextureFilterMode::Nearest:
		return SampleNearest(uv);
	case TTextureFilterMode::Linear:
	default:
		return SampleBilinear(uv);
	}
}