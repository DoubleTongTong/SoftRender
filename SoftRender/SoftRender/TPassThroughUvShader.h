#pragma once

#include "TShader.h"

class TPassThroughUvShader : public TShader
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
};