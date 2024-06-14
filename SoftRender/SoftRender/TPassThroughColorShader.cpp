#include "TPassThroughColorShader.h"

void TPassThroughColorShader::VertexShader(const TShaderContext& context, TVertexShaderOutput& output)
{
	tmath::Vec3f position;
	context.GetAttribute(0, position);

	output.position = projectionMatrix * viewMatrix * modelMatrix * tmath::Vec4f(position, 1.0f);

	output.useColor = true;
	context.GetAttribute(1, output.color);
}

void TPassThroughColorShader::FragmentShader(const TVertexShaderOutput& input, TFragmentShaderOutput& output)
{
	output.color = input.color;
}