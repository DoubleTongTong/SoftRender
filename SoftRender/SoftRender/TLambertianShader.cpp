#include "TLambertianShader.h"

void TLambertianShader::VertexShader(const TShaderContext& context, TVertexShaderOutput& output)
{
	tmath::Vec3f position;
	context.GetAttribute(0, position);

	output.builtin_position = projectionMatrix * viewMatrix * modelMatrix * tmath::Vec4f(position, 1.0f);

	tmath::Vec3f normal;
	context.GetAttribute(1, normal);
	output.variables["normal"] = normal;

	tmath::Vec2f uv;
	context.GetAttribute(2, uv);
	output.variables["uv"] = uv;
}

void TLambertianShader::FragmentShader(
	const TShaderContext& context,
	const TVertexShaderOutput& input,
	TFragmentShaderOutput& output)
{
	tmath::Vec3f normal = std::get<tmath::Vec3f>(input.variables.at("normal"));
	tmath::Vec2f uv = std::get<tmath::Vec2f>(input.variables.at("uv"));

	normal.Normalize();
	tmath::Vec4f surfaceColor = context.texture(uv);
	float NDotL = std::max(tmath::dot(normal, -lightDirection), 0.0f);
	tmath::Vec4f final_color = lightColor * surfaceColor * NDotL;

	final_color += ambientColor * surfaceColor;

	final_color =
	{
		std::clamp(final_color.x(), 0.0f, 1.0f),
		std::clamp(final_color.y(), 0.0f, 1.0f),
		std::clamp(final_color.z(), 0.0f, 1.0f),
		std::clamp(final_color.w(), 0.0f, 1.0f)
	};

	output.color = final_color;
}