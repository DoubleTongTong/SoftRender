#include "TRenderState.h"

TRenderState::TRenderState()
	: m_blendEnabled(false),
	  m_texture(0)
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