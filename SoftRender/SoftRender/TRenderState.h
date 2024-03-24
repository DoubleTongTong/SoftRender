#pragma once

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

	void SetBlend(bool enable);
	bool IsBlendEnabled();
private:
	bool m_blendEnabled;
};