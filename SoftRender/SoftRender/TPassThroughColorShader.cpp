#include "TPassThroughColorShader.h"

void TPassThroughColorShader::VertexShader(const TShaderContext& context, TVertexShaderOutput& output)
{
	tmath::Vec3f position;
	context.GetAttribute(0, position);

	output.builtin_position = projectionMatrix * viewMatrix * modelMatrix * tmath::Vec4f(position, 1.0f);

	tmath::Vec4f color;
	context.GetAttribute(1, color);
	output.variables["color"] = color;
}

void TPassThroughColorShader::FragmentShader(
	const TShaderContext& context,
	const TVertexShaderOutput& input,
	TFragmentShaderOutput& output)
{
	output.color = std::get<tmath::Vec4f>(input.variables.at("color"));
}