#include "TPassThroughUvShader.h"

void TPassThroughUvShader::VertexShader(const TShaderContext& context, TVertexShaderOutput& output)
{
	tmath::Vec3f position;
	context.GetAttribute(0, position);

	output.builtin_position = projectionMatrix * viewMatrix * modelMatrix * tmath::Vec4f(position, 1.0f);

	tmath::Vec2f uv;
	context.GetAttribute(2, uv);
	output.variables["uv"] = uv;
}

void TPassThroughUvShader::FragmentShader(
	const TShaderContext& context,
	const TVertexShaderOutput& input,
	TFragmentShaderOutput& output)
{
	tmath::Vec2f uv = std::get<tmath::Vec2f>(input.variables.at("uv"));
	output.color = context.texture(uv);
}