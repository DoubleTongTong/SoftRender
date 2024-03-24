#include "TRenderState.h"

TRenderState::TRenderState()
	: m_blendEnabled(false)
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