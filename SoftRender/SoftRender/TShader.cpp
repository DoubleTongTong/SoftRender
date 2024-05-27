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