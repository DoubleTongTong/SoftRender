#pragma once

#include "TShader.h"

class TLambertianShader : public TShader
{
public:
	virtual void VertexShader(const TShaderContext& context, TVertexShaderOutput& output) override;
	virtual void FragmentShader(
		const TShaderContext& context,
		const TVertexShaderOutput& input,
		TFragmentShaderOutput& output) override;

public:
	tmath::Mat4f modelMatrix;
	tmath::Mat4f viewMatrix;
	tmath::Mat4f projectionMatrix;

	tmath::Vec3f lightDirection;
	tmath::Vec4f lightColor;
	tmath::Vec4f ambientColor;
};