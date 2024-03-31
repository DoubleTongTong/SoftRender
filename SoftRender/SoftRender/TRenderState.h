#pragma once

#include "TImage.h"

enum class TSampleMode
{
	Nearest,
	Bilinear,
};

enum class TWrapMode
{
	Repeat,
	Mirror,
};

class TRenderState
{
public:
	TRenderState();

	void SetTexture(const TImage* texture);
	const TImage* GetTexture();

	void SetBlend(bool enable);
	bool IsBlendEnabled();

	void SetSampleMode(TSampleMode mode);
	TSampleMode GetSampleMode();
private:
	bool m_blendEnabled;
	const TImage* m_texture;
	TSampleMode m_sampleMode;
};