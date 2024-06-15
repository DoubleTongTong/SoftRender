#include "TShader.h"

TShaderContext::TShaderContext(const TVertexArrayObject* vao)
	: m_vao(vao), m_currentVertexIndex(0)
{
}

void TShaderContext::SetVertexIndex(uint32_t index)
{
	m_currentVertexIndex = index;
}

TShader::~TShader()
{
}

TVertexShaderOutput::TVertexShaderOutput()
	: useColor(false), useUV(false)
{
}

TVertexShaderOutput::~TVertexShaderOutput()
{
}

TVertexShaderOutputPrivate::TVertexShaderOutputPrivate()
	: TVertexShaderOutput()
{
}

TVertexShaderOutputPrivate TVertexShaderOutputPrivate::Lerp(const TVertexShaderOutputPrivate& other, float t) const
{
	TVertexShaderOutputPrivate res;

	res.position = this->position * (1 - t) + other.position * t;

	if (this->useColor)
	{
		res.useColor = true;
		res.color = this->color * (1 - t) + other.color * t;
	}
	else
	{
		res.useUV = true;
		res.uv = this->uv * (1 - t) + other.uv * t;
	}

	return res;
}