#include "TPassThroughUvShader.h"

void TPassThroughUvShader::VertexShader(const TShaderContext& context, TVertexShaderOutput& output)
{
	tmath::Vec3f position;
	context.GetAttribute(0, position);

	output.position = projectionMatrix * viewMatrix * modelMatrix * tmath::Vec4f(position, 1.0f);

	output.useUV = true;
	context.GetAttribute(2, output.uv);
}

void TPassThroughUvShader::FragmentShader(const TVertexShaderOutput& input, TFragmentShaderOutput& output)
{
	output.color = input.color;
}