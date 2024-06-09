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

void TSimpleShader::VertexShader(const TShaderContext& context, TVertexShaderOutput& output)
{
	tmath::Vec3f position;
	context.GetAttribute(0, position);

	output.position = projectionMatrix * viewMatrix * modelMatrix * tmath::Vec4f(position, 1.0f);

	output.useColor = true;
	context.GetAttribute(1, output.color);
}

void TSimpleShader::FragmentShader(const TVertexShaderOutput& input, TFragmentShaderOutput& output)
{
	output.color = input.color;
}

TVertexShaderOutput TVertexShaderOutput::Lerp(const TVertexShaderOutput& other, float t) const
{
	TVertexShaderOutput res;

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