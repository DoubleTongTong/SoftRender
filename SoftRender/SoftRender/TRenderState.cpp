#include "TRenderState.h"

TRenderState::TRenderState()
	: m_blendEnabled(false),
	  m_texture(0),
	  m_sampleMode(TSampleMode::Nearest),
	  m_wrapMode(TWrapMode::Repeat),
	  m_cullEnabled(false),
	  m_cullFace(TCullFace::Back),
	  m_frontFace(TFrontFace::CounterClockwise)
{
}

void TRenderState::SetBlend(bool enable)
{
	m_blendEnabled = enable;
}

bool TRenderState::IsBlendEnabled()
{
	return m_blendEnabled;
}

void TRenderState::SetTexture(const TImage* texture)
{
	m_texture = texture;
}

const TImage* TRenderState::GetTexture()
{
	return m_texture;
}

void TRenderState::SetSampleMode(TSampleMode mode)
{
	m_sampleMode = mode;
}

TSampleMode TRenderState::GetSampleMode()
{
	return m_sampleMode;
}

void TRenderState::SetWrapMode(TWrapMode mode)
{
	m_wrapMode = mode;
}

TWrapMode TRenderState::GetWrapMode()
{
	return m_wrapMode;
}

void TRenderState::SetCulling(bool enabled)
{
	m_cullEnabled = enabled;
}

bool TRenderState::IsCullingEnabled()
{
	return m_cullEnabled;
}

void TRenderState::SetCullFace(TCullFace face)
{
	m_cullFace = face;
}

TCullFace TRenderState::GetCullFace()
{
	return m_cullFace;
}

void TRenderState::SetFrontFace(TFrontFace face)
{
	m_frontFace = face;
}

TFrontFace TRenderState::GetFrontFace()
{
	return m_frontFace;
}