#include "TRenderState.h"

TRenderState::TRenderState()
	: m_blendEnabled(false),
	  m_texture(0),
	  m_sampleMode(TSampleMode::Nearest)
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
