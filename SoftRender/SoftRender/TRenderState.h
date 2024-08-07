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

enum class TCullFace
{
	Back,
	Front,
};

enum class TFrontFace
{
	Clockwise,
	CounterClockwise,
};

enum class TEnableCap
{
	CullFace,
	DepthTest,
	Blend,
};

enum class TDepthFunc
{
	Less,
	LessEqual,
	Greater,
	GreaterEqual,
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

	void SetWrapMode(TWrapMode mode);
	TWrapMode GetWrapMode();

	/**
	 * Culling
	 */
	void SetCulling(bool enabled);
	bool IsCullingEnabled();

	void SetCullFace(TCullFace face);
	TCullFace GetCullFace();

	void SetFrontFace(TFrontFace face);
	TFrontFace GetFrontFace();

	/**
	 * Depth Test
	 */
	void SetDepthTest(bool enabled);
	bool IsDepthTestEnabled();

	void SetDepthFunc(TDepthFunc func);
	TDepthFunc GetDepthFunc();

private:
	bool m_blendEnabled;
	const TImage* m_texture;
	TSampleMode m_sampleMode;
	TWrapMode m_wrapMode;

	bool       m_cullEnabled;
	TCullFace  m_cullFace;
	TFrontFace m_frontFace;

	bool       m_depthTestEnabled;
	TDepthFunc m_depthFunc;
};